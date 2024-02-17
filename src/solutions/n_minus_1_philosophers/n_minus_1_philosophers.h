// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef DPP_SOLUTIONS_N_MINUS_1_PHILOSOPHERS_H_
#define DPP_SOLUTIONS_N_MINUS_1_PHILOSOPHERS_H_

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

constexpr auto kMaxConcurrentPhilosopherCount{kPhilosopherCount - 1};
using PhilosopherSemaphore =
    std::counting_semaphore<kMaxConcurrentPhilosopherCount>;

class Philosopher {
 public:
  Philosopher() = default;
  Philosopher(const Philosopher&) = delete;
  Philosopher(Philosopher&&) = delete;
  Philosopher& operator=(const Philosopher&) = delete;
  Philosopher& operator=(Philosopher&&) = delete;
  virtual ~Philosopher() = default;

  void Materialize(PhilosopherId id, PhilosopherSemaphore*,
                   Chopstick* chopstick1, Chopstick* chopstick2);
  void Think();
  void GetHungry();
  void Eat();

 private:
  void Announce(std::string_view message) const;
  void Sleep() const;

  PhilosopherId id_{kInvalidPhilosopherId};
  PhilosopherState state_{PhilosopherState::Unknown};
  PhilosopherSemaphore* semaphore_{nullptr};
  Chopstick* chopstick1_{nullptr};
  Chopstick* chopstick2_{nullptr};
};

class NMinus1PhilosophersDiningParty : public DiningParty {
 public:
  NMinus1PhilosophersDiningParty() = default;
  NMinus1PhilosophersDiningParty(const NMinus1PhilosophersDiningParty&) =
      delete;
  NMinus1PhilosophersDiningParty(NMinus1PhilosophersDiningParty&&) = delete;
  NMinus1PhilosophersDiningParty& operator=(
      const NMinus1PhilosophersDiningParty&) = delete;
  NMinus1PhilosophersDiningParty& operator=(NMinus1PhilosophersDiningParty&&) =
      delete;
  virtual ~NMinus1PhilosophersDiningParty() = default;

  void Initialize() override;

  void JoinParty(PhilosopherId philosopher_id);

 private:
  std::array<Chopstick, kPhilosopherCount> chopsticks_{};
  std::array<Philosopher, kPhilosopherCount> philosophers_{};
  std::array<std::thread, kPhilosopherCount> threads_{};
  PhilosopherSemaphore semaphore_{kMaxConcurrentPhilosopherCount};
};
}  // namespace dpp

#endif  // DPP_SOLUTIONS_N_MINUS_1_PHILOSOPHERS_H_
