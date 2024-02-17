// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be it in the LICENSE file.

#include "logger.h"

namespace dpp {
Logger& Logger::Get() {
  if (logger_ == nullptr) {
    logger_ = Generate();
  }

  return *logger_.get();
}

std::unique_ptr<Logger> Logger::Generate() {
  return std::make_unique<Logger>();
}
}  // namespace dpp
