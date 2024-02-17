// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be it in the LICENSE file.

#include "utils.h"

namespace dpp {
s32 GenerateRandomS32(s32 min, s32 max) {
  static std::random_device random_device{};
  static std::mt19937 engine{random_device()};

  std::uniform_int_distribution<s32> distribution{min, max};
  return distribution(engine);
}

void SleepMs(u32 time_in_ms) {
  std::this_thread::sleep_for(std::chrono::milliseconds(time_in_ms));
}
}  // namespace dpp
