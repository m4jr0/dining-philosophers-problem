// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef COMET_COMET_ENTRY_POINT_H_
#define COMET_COMET_ENTRY_POINT_H_

#include "dpp_precompile.h"

#include "common/dining_party.h"

namespace dpp {
extern std::unique_ptr<DiningParty> GenerateDiningParty();
}  // namespace dpp

#endif  // COMET_COMET_ENTRY_POINT_H_
