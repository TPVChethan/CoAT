// Copyright (c) 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Input buffer layout, dividing the total buffer into regions (r0_ - r5_):
//
// |----------------|-----------------------------------------|----------------|
//
//                                   kBlockSize + kKernelSize / 2
//                   <--------------------------------------------------------->
//                                              r0_
//
//  kKernelSize / 2   kKernelSize / 2         kKernelSize / 2   kKernelSize / 2
// <---------------> <--------------->       <---------------> <--------------->
//        r1_               r2_                     r3_               r4_
//
//                                                     kBlockSize
//                                     <--------------------------------------->
//                                                        r5_
//
// The algorithm:
//
// 1) Consume input frames into r0_ (r1_ is zero-initialized).
// 2) Position kernel centered at start of r0_ (r2_) and generate output frames
//    until kernel is centered at start of r4_ or we've finished generating all
//    the output frames.
// 3) Copy r3_ to r1_ and r4_ to r2_.
// 4) Consume input frames into r5_ (zero-pad if we run out of input).
// 5) Goto (2) until all of input is consumed.
//
// Note: we're glossing over how the sub-sample handling works with
// |virtual_source_idx_|, etc.

#include "media/base/interleaved_sinc_resampler.h"

#include <algorithm>
#include <cmath>

#include "base/logging.h"

namespace media {

namespace {

// The kernel size can be adjusted for quality (higher is better) at the
// expense of performance.  Must be a multiple of 32.
const int kKernelSize = 32;

// The number of destination frames generated per processing pass.  Affects
// how often and for how much InterleavedSincResampler calls back for input.
// Must be greater than kKernelSize.
const int kBlockSize = 512;

// The kernel offset count is used for interpolation and is the number of
// sub-sample kernel shifts.  Can be adjusted for quality (higher is better)
// at the expense of allocating more memory.
const int kKernelOffsetCount = 32;
const int kKernelStorageSize = kKernelSize * (kKernelOffsetCount + 1);

// The size (in samples) of the internal buffer used by the resampler.
const int kBufferSize = kBlockSize + kKernelSize;

// The maximum numbers of buffer can be queued.
const int kMaximumPendingBuffers = 8;

}  // namespace

InterleavedSincResampler::InterleavedSincResampler(double io_sample_rate_ratio,
                                                   int channel_count)
    : io_sample_rate_ratio_(io_sample_rate_ratio),
      virtual_source_idx_(0),
      buffer_primed_(false),
      channel_count_(channel_count),
      frame_size_in_bytes_(sizeof(float) * channel_count_),
      // Create buffers with a 16-byte alignment for possible optimizations.
      kernel_storage_(static_cast<float*>(
          base::AlignedAlloc(sizeof(float) * kKernelStorageSize, 16))),
      input_buffer_(static_cast<float*>(
          base::AlignedAlloc(frame_size_in_bytes_ * kBufferSize, 16))),
      offset_in_frames_(0),
      frames_resampled_(0),
      frames_queued_(0),
      // Setup various region pointers in the buffer (see diagram above).
      r0_(input_buffer_.get() + kKernelSize / 2 * channel_count_),
      r1_(input_buffer_.get()),
      r2_(r0_),
      r3_(r0_ + (kBlockSize - kKernelSize / 2) * channel_count_),
      r4_(r0_ + kBlockSize * channel_count_),
      r5_(r0_ + kKernelSize / 2 * channel_count_) {
  // Ensure kKernelSize is a multiple of 32 for easy SSE optimizations; causes
  // r0_ and r5_ (used for input) to always be 16-byte aligned by virtue of
  // input_buffer_ being 16-byte aligned.
  DCHECK_EQ(kKernelSize % 32, 0) << "kKernelSize must be a multiple of 32!";
  DCHECK_GT(kBlockSize, kKernelSize)
      << "kBlockSize must be greater than kKernelSize!";
  // Basic sanity checks to ensure buffer regions are laid out correctly:
  // r0_ and r2_ should always be the same position.
  DCHECK_EQ(r0_, r2_);
  // r1_ at the beginning of the buffer.
  DCHECK_EQ(r1_, input_buffer_.get());
  // r1_ left of r2_, r2_ left of r5_ and r1_, r2_ size correct.
  DCHECK_EQ(r2_ - r1_, r5_ - r2_);
  // r3_ left of r4_, r5_ left of r0_ and r3_ size correct.
  DCHECK_EQ(r4_ - r3_, r5_ - r0_);
  // r3_, r4_ size correct and r4_ at the end of the buffer.
  DCHECK_EQ(r4_ + (r4_ - r3_), r1_ + kBufferSize * channel_count_);
  // r5_ size correct and at the end of the buffer.
  DCHECK_EQ(r5_ + kBlockSize * channel_count_,
            r1_ + kBufferSize * channel_count_);

  memset(kernel_storage_.get(), 0,
         sizeof(*kernel_storage_.get()) * kKernelStorageSize);
  memset(input_buffer_.get(), 0, frame_size_in_bytes_ * kBufferSize);

  InitializeKernel();
}

void InterleavedSincResampler::InitializeKernel() {
  // Blackman window parameters.
  static const double kAlpha = 0.16;
  static const double kA0 = 0.5 * (1.0 - kAlpha);
  static const double kA1 = 0.5;
  static const double kA2 = 0.5 * kAlpha;

  // |sinc_scale_factor| is basically the normalized cutoff frequency of the
  // low-pass filter.
  double sinc_scale_factor =
      io_sample_rate_ratio_ > 1.0 ? 1.0 / io_sample_rate_ratio_ : 1.0;

  // The sinc function is an idealized brick-wall filter, but since we're
  // windowing it the transition from pass to stop does not happen right away.
  // So we should adjust the low pass filter cutoff slightly downward to avoid
  // some aliasing at the very high-end.
  // TODO(crogers): this value is empirical and to be more exact should vary
  // depending on kKernelSize.
  sinc_scale_factor *= 0.9;

  // Generates a set of windowed sinc() kernels.
  // We generate a range of sub-sample offsets from 0.0 to 1.0.
  for (int offset_idx = 0; offset_idx <= kKernelOffsetCount; ++offset_idx) {
    double subsample_offset =
        static_cast<double>(offset_idx) / kKernelOffsetCount;

    for (int i = 0; i < kKernelSize; ++i) {
      // Compute the sinc with offset.
      double s =
          sinc_scale_factor * M_PI * (i - kKernelSize / 2 - subsample_offset);
      double sinc = (!s ? 1.0 : sin(s) / s) * sinc_scale_factor;

      // Compute Blackman window, matching the offset of the sinc().
      double x = (i - subsample_offset) / kKernelSize;
      double window =
          kA0 - kA1 * cos(2.0 * M_PI * x) + kA2 * cos(4.0 * M_PI * x);

      // Window the sinc() function and store at the correct offset.
      kernel_storage_.get()[i + offset_idx * kKernelSize] = sinc * window;
    }
  }
}

void InterleavedSincResampler::QueueBuffer(
    const scoped_refptr<::media::Buffer>& buffer) {
  DCHECK(buffer);
  DCHECK(CanQueueBuffer());

  if (!pending_buffers_.empty() && pending_buffers_.back()->IsEndOfStream()) {
    DCHECK(buffer->IsEndOfStream());
    return;
  }

  if (!buffer->IsEndOfStream()) {
    frames_queued_ += buffer->GetDataSize() / frame_size_in_bytes_;
  }

  pending_buffers_.push(buffer);
}

bool InterleavedSincResampler::Resample(float* destination, int frames) {
  if (!HasEnoughData(frames)) {
    return false;
  }

  int remaining_frames = frames;

  // Step (1) -- Prime the input buffer at the start of the input stream.
  if (!buffer_primed_) {
    Read(r0_, kBlockSize + kKernelSize / 2);
    buffer_primed_ = true;
  }

  // Step (2) -- Resample!
  while (remaining_frames) {
    while (virtual_source_idx_ < kBlockSize) {
      // |virtual_source_idx_| lies in between two kernel offsets so figure out
      // what they are.
      int source_idx = static_cast<int>(virtual_source_idx_);
      double subsample_remainder = virtual_source_idx_ - source_idx;

      double virtual_offset_idx = subsample_remainder * kKernelOffsetCount;
      int offset_idx = static_cast<int>(virtual_offset_idx);

      // We'll compute "convolutions" for the two kernels which straddle
      // |virtual_source_idx_|.
      float* k1 = kernel_storage_.get() + offset_idx * kKernelSize;
      float* k2 = k1 + kKernelSize;

      // Initialize input pointer based on quantized |virtual_source_idx_|.
      float* input_ptr = r1_ + source_idx * channel_count_;

      // Figure out how much to weight each kernel's "convolution".
      double kernel_interpolation_factor = virtual_offset_idx - offset_idx;
      for (int i = 0; i < channel_count_; ++i) {
        *destination++ =
            Convolve(input_ptr + i, k1, k2, kernel_interpolation_factor);
      }

      // Advance the virtual index.
      virtual_source_idx_ += io_sample_rate_ratio_;

      if (!--remaining_frames) {
        frames_resampled_ += frames;
        return true;
      }
    }

    // Wrap back around to the start.
    virtual_source_idx_ -= kBlockSize;

    // Step (3) Copy r3_ to r1_ and r4_ to r2_.
    // This wraps the last input frames back to the start of the buffer.
    memcpy(r1_, r3_, frame_size_in_bytes_ * (kKernelSize / 2));
    memcpy(r2_, r4_, frame_size_in_bytes_ * (kKernelSize / 2));

    // Step (4)
    // Refresh the buffer with more input.
    Read(r5_, kBlockSize);
  }

  NOTREACHED();
  return false;
}

void InterleavedSincResampler::Flush() {
  virtual_source_idx_ = 0;
  buffer_primed_ = false;
  memset(input_buffer_.get(), 0, frame_size_in_bytes_ * kBufferSize);
  while (!pending_buffers_.empty()) {
    pending_buffers_.pop();
  }
  offset_in_frames_ = 0;
  frames_resampled_ = 0;
  frames_queued_ = 0;
}

bool InterleavedSincResampler::CanQueueBuffer() const {
  if (pending_buffers_.empty()) {
    return true;
  }
  if (pending_buffers_.back()->IsEndOfStream()) {
    return false;
  }
  return pending_buffers_.size() < kMaximumPendingBuffers;
}

bool InterleavedSincResampler::ReachedEOS() const {
  if (pending_buffers_.empty() || !pending_buffers_.back()->IsEndOfStream()) {
    return false;
  }
  return frames_resampled_ * io_sample_rate_ratio_ >= frames_queued_;
}

bool InterleavedSincResampler::HasEnoughData(int frames_to_resample) const {
  // Always return true if EOS is seen, as in this case we will just fill 0.
  if (!pending_buffers_.empty() && pending_buffers_.back()->IsEndOfStream()) {
    return true;
  }

  // We have to decrease frames_queued_ down as the Read()s are always done in
  // blocks of kBlockSize or kBufferSize. We have to ensure that there is buffer
  // for an extra Read().
  return (frames_resampled_ + frames_to_resample) * io_sample_rate_ratio_ <
         frames_queued_ - kBufferSize;
}

void InterleavedSincResampler::Read(float* destination, int frames) {
  while (frames > 0 && !pending_buffers_.empty()) {
    scoped_refptr<Buffer> buffer = pending_buffers_.front();
    if (buffer->IsEndOfStream()) {
      // Zero fill the buffer after EOS has reached.
      memset(destination, 0, frame_size_in_bytes_ * frames);
      return;
    }
    // Copy the data over.
    int frames_in_buffer = buffer->GetDataSize() / frame_size_in_bytes_;
    int frames_to_copy = std::min(frames_in_buffer - offset_in_frames_, frames);
    const uint8* source = buffer->GetData();
    source += frame_size_in_bytes_ * offset_in_frames_;
    memcpy(destination, source, frame_size_in_bytes_ * frames_to_copy);
    offset_in_frames_ += frames_to_copy;
    // Pop the first buffer if all its content has been read.
    if (offset_in_frames_ == frames_in_buffer) {
      offset_in_frames_ = 0;
      pending_buffers_.pop();
    }
    frames -= frames_to_copy;
    destination += frames_to_copy * channel_count_;
  }

  // Read should always be satisfied as otherwise Resample should return false
  // to the caller directly.
  DCHECK_EQ(frames, 0);
}

float InterleavedSincResampler::Convolve(const float* input_ptr,
                                         const float* k1,
                                         const float* k2,
                                         double kernel_interpolation_factor) {
  float sum1 = 0;
  float sum2 = 0;

  // Generate a single output sample.  Unrolling this loop hurt performance in
  // local testing.
  int n = kKernelSize;
  while (n--) {
    sum1 += *input_ptr * *k1++;
    sum2 += *input_ptr * *k2++;
    input_ptr += channel_count_;
  }

  // Linearly interpolate the two "convolutions".
  return (1.0 - kernel_interpolation_factor) * sum1 +
         kernel_interpolation_factor * sum2;
}

}  // namespace media