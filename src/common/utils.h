// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef DPP_COMMON_UTILS_H_
#define DPP_COMMON_UTILS_H_

#include "dpp_precompile.h"

namespace dpp {
s32 GenerateRandomS32(s32 min, s32 max);

void SleepMs(u32 time_in_ms);
}  // namespace dpp

#endif  // DPP_COMMON_UTILS_H_
