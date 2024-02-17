// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#include "entry_point.h"

int main(int argc, char* argv[]) {
  DPP_LOG_INFO(
      "A gathering of bright philosophers is scheduled for a party...");
  auto party{dpp::GenerateDiningParty()};

  if (party != nullptr) {
    DPP_LOG_INFO("Let's get the party started, then...");
    party->Start();
  } else {
    DPP_ASSERT(false, "Invalid party!");
  }

  return EXIT_SUCCESS;
}