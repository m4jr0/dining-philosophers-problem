// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be it in the LICENSE file.

#include "central_arbitor.h"

namespace dpp {
Waiter::Waiter(std::array<Philosopher, kPhilosopherCount>* philosophers)
    : philosophers_{philosophers} {}

bool Waiter::RequestChopsticks(PhilosopherId philosopher_id) {
  std::lock_guard<std::mutex> lock(mutex_);

  auto prev_philosopher_id{(philosopher_id + 1 + kPhilosopherCount) %
                           kPhilosopherCount};
  auto next_philosopher_id{(philosopher_id - 1) % kPhilosopherCount};

  if (philosophers_->at(prev_philosopher_id).GetState() ==
          PhilosopherState::Eating ||
      philosophers_->at(next_philosopher_id).GetState() ==
          PhilosopherState::Eating) {
    return false;
  }

  return true;
}

void Philosopher::Materialize(PhilosopherId id, Waiter* waiter) {
  id_ = id;
  state_ = PhilosopherState::Materialized;
  waiter_ = waiter;
  Announce("I am joining the party!");
  Sleep();
}

void Philosopher::Think() {
  state_ = PhilosopherState::Thinking;
  Announce("I am thinking.");
  Sleep();
}

void Philosopher::GetHungry() {
  state_ = PhilosopherState::Hungry;
  Announce("I am hungry.");
}

void Philosopher::Eat() {
  while (!waiter_->RequestChopsticks(id_)) {
    SleepMs(kEatAttemptDelayInMs_);
  }

  state_ = PhilosopherState::Eating;
  Announce("I am eating.");
  Sleep();
}

PhilosopherState Philosopher::GetState() const noexcept { return state_; }

void Philosopher::Announce(std::string_view message) const {
  DPP_LOG_INFO("Philosopher #", id_, ": ", message);
}

void Philosopher::Sleep() const {
  SleepMs(GenerateRandomS32(0, kMaxSleepTimeInMs));
}

void CentralArbitorDiningParty::Initialize() {
  for (auto i{0}; i < kPhilosopherCount; ++i) {
    threads_[i] = std::thread(&CentralArbitorDiningParty::JoinParty, this,
                              static_cast<PhilosopherId>(i));
  }

  for (auto i{0}; i < kPhilosopherCount; ++i) {
    threads_[i].join();
  }
}

void CentralArbitorDiningParty::JoinParty(PhilosopherId philosopher_id) {
  auto& philosopher{philosophers_[philosopher_id]};
  philosopher.Materialize(philosopher_id, &waiter_);

  while (is_partying_.load()) {
    philosopher.Think();
    philosopher.GetHungry();
    philosopher.Eat();
  }
}

std::unique_ptr<DiningParty> GenerateDiningParty() {
  return std::make_unique<CentralArbitorDiningParty>();
}
}  // namespace dpp
