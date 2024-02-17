// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#include "debug.h"

#include "common/logger.h"

namespace dpp {
void HandleCriticalError() { DPP_LOG_ERROR("Aborting."); }
}  // namespace dpp
