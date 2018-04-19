// Copyright 2017 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "starboard/audio_sink.h"

#include "starboard/log.h"

bool SbAudioSinkIsAudioSampleTypeSupported(
    SbMediaAudioSampleType audio_sample_type) {
  switch (audio_sample_type) {
#if SB_HAS_QUIRK(SUPPORT_INT16_AUDIO_SAMPLES)
    case kSbMediaAudioSampleTypeInt16:
      return true;
#endif  // SB_HAS_QUIRK(SUPPORT_INT16_AUDIO_SAMPLES)
    case kSbMediaAudioSampleTypeFloat32:
      return true;
    default:
      SB_NOTREACHED();
      return false;
  }
}
