// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be it in the LICENSE file.

#include "n_minus_1_philosophers.h"

namespace dpp {
void Philosopher::Materialize(PhilosopherId id, PhilosopherSemaphore* semaphore,
                              Chopstick* chopstick1, Chopstick* chopstick2) {
  id_ = id;
  state_ = PhilosopherState::Materialized;
  semaphore_ = semaphore;
  chopstick1_ = chopstick1;
  chopstick2_ = chopstick2;
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
  semaphore_->acquire();

  {
    std::lock_guard<std::mutex> lock1(chopstick1_->mutex);

    {
      std::lock_guard<std::mutex> lock2(chopstick2_->mutex);

      state_ = PhilosopherState::Eating;
      Announce("I am eating.");
      Sleep();
    }
  }

  semaphore_->release();
}

void Philosopher::Announce(std::string_view message) const {
  DPP_LOG_INFO("Philosopher #", id_, ": ", message);
}

void Philosopher::Sleep() const {
  SleepMs(GenerateRandomS32(0, kMaxSleepTimeInMs));
}

void NMinus1PhilosophersDiningParty::Initialize() {
  for (auto i{0}; i < kPhilosopherCount; ++i) {
    threads_[i] = std::thread(&NMinus1PhilosophersDiningParty::JoinParty, this,
                              static_cast<PhilosopherId>(i));
  }

  for (auto i{0}; i < kPhilosopherCount; ++i) {
    threads_[i].join();
  }
}

void NMinus1PhilosophersDiningParty::JoinParty(PhilosopherId philosopher_id) {
  auto& philosopher{philosophers_[philosopher_id]};

  auto philosopher_index{static_cast<uindex>(philosopher_id)};

  // For each philosopher, the convention is to initially pick up their left
  // chopstick, followed by the right one.
  auto first_chopstick_index{philosopher_index % kPhilosopherCount};
  auto second_chopstick_index{(philosopher_index + 1 + kPhilosopherCount) %
                              kPhilosopherCount};

  philosopher.Materialize(philosopher_id, &semaphore_,
                          &chopsticks_[first_chopstick_index],
                          &chopsticks_[second_chopstick_index]);

  while (is_partying_.load()) {
    philosopher.Think();
    philosopher.GetHungry();
    philosopher.Eat();
  }
}

std::unique_ptr<DiningParty> GenerateDiningParty() {
  return std::make_unique<NMinus1PhilosophersDiningParty>();
}
}  // namespace dpp
