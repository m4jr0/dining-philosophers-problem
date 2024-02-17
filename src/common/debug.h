// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef DPP_COMMON_DEBUG_H_
#define DPP_COMMON_DEBUG_H_

#include <stdio.h>

#include <cassert>

#include "common/logger.h"

#if defined(_MSC_VER)
#if defined(_CPPRTTI)
#define DPP_RTTI
#endif  // _CPPRTTI
// _MSC_VER
#elif defined(__clang__)
#if __has_feature(cxx_rtti)
#define DPP_RTTI
#endif  // __has_feature(cxx_rtti)
// defined(__clang__)
#elif defined(__GNUG__)
#if defined(__GXX_RTTI)
#define DPP_RTTI
#endif  // __GXX_RTTI
#endif  // defined(__GNUG__)

namespace dpp {
void HandleCriticalError();
}  // namespace dpp

#ifndef DPP_DEBUG
#define DPP_ASSERT(assertion, ...)
#else
#define DPP_ASSERT(assertion, ...)                       \
  do {                                                   \
    const auto isOk{static_cast<bool>(assertion)};       \
                                                         \
    if (!isOk) {                                         \
      DPP_LOG_ERROR("[CRITICAL FAILURE] ", __VA_ARGS__); \
      dpp::HandleCriticalError();                        \
    }                                                    \
                                                         \
    assert(isOk);                                        \
  } while (false)
#endif

#endif  // DPP_COMMON_DEBUG_H_
