/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkDebugfTracer_DEFINED
#define SkDebugfTracer_DEFINED

#include "SkEventTracer.h"
#include "SkString.h"

/**
 * A SkEventTracer implementation that logs events using SkDebugf.
 */
class SkDebugfTracer : public SkEventTracer {
public:
    SkDebugfTracer() {}

    SkEventTracer::Handle addTraceEvent(char phase,
                                        const uint8_t* categoryEnabledFlag,
                                        const char* name,
                                        uint64_t id,
                                        int numArgs,
                                        const char** argNames,
                                        const uint8_t* argTypes,
                                        const uint64_t* argValues,
                                        uint8_t flags) override;

    void updateTraceEventDuration(const uint8_t* categoryEnabledFlag,
                                  const char* name,
                                  SkEventTracer::Handle handle) override;

    const uint8_t* getCategoryGroupEnabled(const char* name) override;

    const char* getCategoryGroupName(const uint8_t* categoryEnabledFlag) override {
        static const char* category = "category?";
        return category;
    }

private:
    SkString fIndent;
    int fCnt = 0;
};

#endif
