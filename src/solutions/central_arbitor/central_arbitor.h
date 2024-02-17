// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef DPP_SOLUTIONS_CENTRAL_ARBITOR_H_
#define DPP_SOLUTIONS_CENTRAL_ARBITOR_H_

#include "dpp_precompile.h"

#include "common/dining_party.h"

namespace dpp {
class Philosopher;

using PhilosopherId = uindex;
constexpr auto kInvalidPhilosopherId{static_cast<PhilosopherId>(-1)};

enum class PhilosopherState {
  Unknown = 0,
  Materialized,
  Thinking,
  Hungry,
  Eating
};

class Waiter {
 public:
  Waiter(std::array<Philosopher, kPhilosopherCount>* philosophers);
  Waiter(const Waiter&) = delete;
  Waiter(Waiter&&) = delete;
  Waiter& operator=(const Waiter&) = delete;
  Waiter& operator=(Waiter&&) = delete;
  virtual ~Waiter() = default;

  bool RequestChopsticks(PhilosopherId philosopher_id);

 private:
  std::mutex mutex_{};
  std::array<Philosopher, kPhilosopherCount>* philosophers_{nullptr};
};

class Philosopher {
 public:
  Philosopher() = default;
  Philosopher(const Philosopher&) = delete;
  Philosopher(Philosopher&&) = delete;
  Philosopher& operator=(const Philosopher&) = delete;
  Philosopher& operator=(Philosopher&&) = delete;
  virtual ~Philosopher() = default;

  void Materialize(PhilosopherId id, Waiter* waiter);
  void Think();
  void GetHungry();
  void Eat();

  PhilosopherState GetState() const noexcept;

 private:
  void Announce(std::string_view message) const;
  void Sleep() const;

  static constexpr auto kEatAttemptDelayInMs_{300};

  PhilosopherId id_{kInvalidPhilosopherId};
  PhilosopherState state_{PhilosopherState::Unknown};
  Waiter* waiter_{nullptr};
};

class CentralArbitorDiningParty : public DiningParty {
 public:
  CentralArbitorDiningParty() = default;
  CentralArbitorDiningParty(const CentralArbitorDiningParty&) = delete;
  CentralArbitorDiningParty(CentralArbitorDiningParty&&) = delete;
  CentralArbitorDiningParty& operator=(const CentralArbitorDiningParty&) =
      delete;
  CentralArbitorDiningParty& operator=(CentralArbitorDiningParty&&) = delete;
  virtual ~CentralArbitorDiningParty() = default;

  void Initialize() override;

  void JoinParty(PhilosopherId philosopher_id);

 private:
  std::array<Philosopher, kPhilosopherCount> philosophers_{};
  std::array<std::thread, kPhilosopherCount> threads_{};
  Waiter waiter_{&philosophers_};
};
}  // namespace dpp

#endif  // DPP_SOLUTIONS_CENTRAL_ARBITOR_H_
