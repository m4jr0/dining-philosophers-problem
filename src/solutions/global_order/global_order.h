// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef DPP_SOLUTIONS_GLOBAL_ORDER_H_
#define DPP_SOLUTIONS_GLOBAL_ORDER_H_

#include "dpp_precompile.h"

#include "common/dining_party.h"

namespace dpp {
struct Chopstick {
  std::mutex mutex{};
};

using PhilosopherId = uindex;
constexpr auto kInvalidPhilosopherId{static_cast<PhilosopherId>(-1)};

enum class PhilosopherState {
  Unknown = 0,
  Materialized,
  Thinking,
  Hungry,
  Eating
};

class Philosopher {
 public:
  Philosopher() = default;
  Philosopher(const Philosopher&) = delete;
  Philosopher(Philosopher&&) = delete;
  Philosopher& operator=(const Philosopher&) = delete;
  Philosopher& operator=(Philosopher&&) = delete;
  virtual ~Philosopher() = default;

  void Materialize(PhilosopherId id, Chopstick* chopstick1,
                   Chopstick* chopstick2);
  void Think();
  void GetHungry();
  void Eat();

 private:
  void Announce(std::string_view message) const;
  void Sleep() const;

  PhilosopherId id_{kInvalidPhilosopherId};
  PhilosopherState state_{PhilosopherState::Unknown};
  Chopstick* chopstick1_{nullptr};
  Chopstick* chopstick2_{nullptr};
};

class GlobalOrderDiningParty : public DiningParty {
 public:
  GlobalOrderDiningParty() = default;
  GlobalOrderDiningParty(const GlobalOrderDiningParty&) = delete;
  GlobalOrderDiningParty(GlobalOrderDiningParty&&) = delete;
  GlobalOrderDiningParty& operator=(const GlobalOrderDiningParty&) = delete;
  GlobalOrderDiningParty& operator=(GlobalOrderDiningParty&&) = delete;
  virtual ~GlobalOrderDiningParty() = default;

  void Initialize() override;

  void JoinParty(PhilosopherId philosopher_id);

 private:
  std::array<Chopstick, kPhilosopherCount> chopsticks_{};
  std::array<Philosopher, kPhilosopherCount> philosophers_{};
  std::array<std::thread, kPhilosopherCount> threads_{};
};
}  // namespace dpp

#endif  // DPP_SOLUTIONS_GLOBAL_ORDER_H_
