// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef DPP_PRECOMPILE_H_
#define DPP_PRECOMPILE_H_

#include <array>
#include <atomic>
#include <cassert>
#include <chrono>
#include <iostream>
#include <limits>
#include <memory>
#include <mutex>
#include <random>
#include <semaphore>
#include <string_view>
#include <thread>

// Order is really important here.
#include "common/compiler.h"
#include "common/os.h"

#ifdef DPP_WINDOWS
#define NOMINMAX
#include <windows.h>
#endif  // DPP_WINDOWS

#include "common/primitive.h"
#include "common/debug.h"
#include "common/utils.h"

#endif  // DPP_PRECOMPILE_H_
