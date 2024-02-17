// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef DPP_COMMON_DINING_PARTY_H_
#define DPP_COMMON_DINING_PARTY_H_

#include "dpp_precompile.h"

namespace dpp {
constexpr uindex kPhilosopherCount{5};
constexpr auto kMaxSleepTimeInMs{3000};

class DiningParty {
 public:
  static DiningParty& Get();

  DiningParty(const DiningParty&) = delete;
  DiningParty(DiningParty&&) = delete;
  DiningParty& operator=(const DiningParty&) = delete;
  DiningParty& operator=(DiningParty&&) = delete;
  virtual ~DiningParty() = default;

  void Start();
  void Stop();
  virtual void Initialize() = 0;

 protected:
  DiningParty();

  inline static DiningParty* party_{nullptr};
  std::atomic<bool> is_partying_{false};

 private:
#ifdef DPP_WINDOWS
  static BOOL WINAPI HandleConsole(DWORD window_event);
#endif  // DPP_WINDOWS
};

std::unique_ptr<DiningParty> GenerateDiningParty();
}  // namespace dpp

#endif  // DPP_COMMON_DINING_PARTY_H_