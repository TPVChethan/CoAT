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

#ifndef STARBOARD_SHARED_WIN32_THREAD_LOCAL_INTERNAL_H_
#define STARBOARD_SHARED_WIN32_THREAD_LOCAL_INTERNAL_H_

#include <windows.h>

#include "starboard/thread.h"

namespace starboard {
namespace shared {
namespace win32 {

DWORD TlsInternalAlloc(SbThreadLocalDestructor destructor_fn);
void TlsInternalFree(DWORD key);

void* TlsInternalGetValue(DWORD key);
bool TlsInternalSetValue(DWORD key, void* value);

}  // namespace win32
}  // namespace shared
}  // namespace starboard

#endif  // STARBOARD_SHARED_WIN32_THREAD_LOCAL_INTERNAL_H_
