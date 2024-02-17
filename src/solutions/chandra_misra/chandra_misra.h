// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef DPP_SOLUTIONS_CHANDRA_MISRA_H_
#define DPP_SOLUTIONS_CHANDRA_MISRA_H_

// This solution violates the rule that philosophers should not communicate with
// each other by incorporating request messages.
//
// For further details, please refer to the paper:
// K. M. Chandy and J. Misra. 1984. The drinking philosophers problem. ACM
// Trans. Program. Lang. Syst. 6, 4 (Oct. 1984), 632–646.
// https://doi.org/10.1145/1780.1804

#include "dpp_precompile.h"

#include "common/dining_party.h"

namespace dpp {
using PhilosopherId = uindex;
constexpr auto kInvalidPhilosopherId{static_cast<PhilosopherId>(-1)};

struct Chopstick {
  bool is_dirty{true};
  std::condition_variable clean_condition{};
  std::mutex request_token{};
};

enum class PhilosopherState {
  Unknown = 0,
  Materialized,
  Thinking,
  Hungry,
  Eating
};

using Direction = uchar;
constexpr auto kDirectionCount{2};
constexpr auto kLeftDirection{0};
constexpr auto kRightDirection{1};

class Philosopher {
 public:
  Philosopher() = default;
  Philosopher(const Philosopher&) = delete;
  Philosopher(Philosopher&&) = delete;
  Philosopher& operator=(const Philosopher&) = delete;
  Philosopher& operator=(Philosopher&&) = delete;
  virtual ~Philosopher() = default;

  void Materialize(PhilosopherId id,
                   std::array<Chopstick*, kDirectionCount> chopsticks,
                   std::array<Philosopher*, kDirectionCount> neighbors,
                   bool has_left_chopstick, bool has_right_chopstick);
  void Think();
  void GetHungry();
  void Eat();

 private:
  void Announce(std::string_view message) const;
  void Sleep() const;

  void RequestChopstick(Direction direction);
  void ReleaseChopstick(Direction direction);
  bool ReceiveChopstickRequest(Direction direction);

  PhilosopherId id_{kInvalidPhilosopherId};
  PhilosopherState state_{PhilosopherState::Unknown};
  std::array<Chopstick*, kDirectionCount> chopsticks_{nullptr};
  std::array<Philosopher*, kDirectionCount> neighbors_{nullptr};
  std::array<bool, kDirectionCount> has_chopsticks_{false};
};

class ChandraMisraDiningParty : public DiningParty {
 public:
  ChandraMisraDiningParty() = default;
  ChandraMisraDiningParty(const ChandraMisraDiningParty&) = delete;
  ChandraMisraDiningParty(ChandraMisraDiningParty&&) = delete;
  ChandraMisraDiningParty& operator=(const ChandraMisraDiningParty&) = delete;
  ChandraMisraDiningParty& operator=(ChandraMisraDiningParty&&) = delete;
  virtual ~ChandraMisraDiningParty() = default;

  void Initialize() override;

  void JoinParty(PhilosopherId philosopher_id);

 private:
  std::array<Chopstick, kPhilosopherCount> chopsticks_{};
  std::array<Philosopher, kPhilosopherCount> philosophers_{};
  std::array<std::thread, kPhilosopherCount> threads_{};
};
}  // namespace dpp

#endif  // DPP_SOLUTIONS_CHANDRA_MISRA_H_
