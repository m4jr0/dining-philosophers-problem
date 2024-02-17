// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be it in the LICENSE file.

#include "chandra_misra.h"

namespace dpp {
void Philosopher::Materialize(
    PhilosopherId id, std::array<Chopstick*, kDirectionCount> chopsticks,
    std::array<Philosopher*, kDirectionCount> neighbors,
    bool has_left_chopstick, bool has_right_chopstick) {
  id_ = id;
  state_ = PhilosopherState::Materialized;
  chopsticks_ = std::move(chopsticks);
  neighbors_ = std::move(neighbors);

  Announce("I am joining the party!");
  Sleep();
}

void Philosopher::Think() {
  state_ = PhilosopherState::Thinking;
  ReleaseChopstick(kLeftDirection);
  ReleaseChopstick(kRightDirection);
  Announce("I am thinking.");
  Sleep();
}

void Philosopher::GetHungry() {
  state_ = PhilosopherState::Hungry;
  Announce("I am hungry.");
}

void Philosopher::Eat() {
  RequestChopstick(kLeftDirection);
  RequestChopstick(kRightDirection);
  state_ = PhilosopherState::Eating;
  Sleep();
}

void Philosopher::Announce(std::string_view message) const {
  DPP_LOG_INFO("Philosopher #", id_, ": ", message);
}

void Philosopher::Sleep() const {
  SleepMs(GenerateRandomS32(0, kMaxSleepTimeInMs));
}

void Philosopher::RequestChopstick(Direction direction) {
  if (has_chopsticks_[direction]) {
    return;
  }

  auto* chopstick{chopsticks_[direction]};
  auto& neighbor{neighbors_[direction]};

  // Take the opposite direction (from the neighbor point of view).
  auto opposite_direction{(direction + 1) % kDirectionCount};
  std::unique_lock<std::mutex> lock(chopstick->request_token);

  neighbor->ReceiveChopstickRequest(opposite_direction);

  chopstick->clean_condition.wait(
      lock, [&chopstick] { return !chopstick->is_dirty; });

  has_chopsticks_[direction] = true;
  chopstick->is_dirty = true;
}

void Philosopher::ReleaseChopstick(Direction direction) {
  auto* chopstick{chopsticks_[direction]};
  chopstick->is_dirty = false;
  has_chopsticks_[direction] = false;
  chopstick->clean_condition.notify_one();
}

bool Philosopher::ReceiveChopstickRequest(Direction direction) {
  auto* chopstick{chopsticks_[direction]};

  if (!has_chopsticks_[direction]) {
    return false;
  }

  auto is_dirty{chopstick->is_dirty};

  if (is_dirty) {
    chopstick->is_dirty = false;
    chopstick->clean_condition.notify_one();
  }

  return is_dirty;
}

void ChandraMisraDiningParty::Initialize() {
  for (auto i{0}; i < kPhilosopherCount; ++i) {
    threads_[i] = std::thread(&ChandraMisraDiningParty::JoinParty, this,
                              static_cast<PhilosopherId>(i));
  }

  for (auto i{0}; i < kPhilosopherCount; ++i) {
    threads_[i].join();
  }
}

void ChandraMisraDiningParty::JoinParty(PhilosopherId philosopher_id) {
  auto& philosopher{philosophers_[philosopher_id]};

  auto philosopher_index{static_cast<uindex>(philosopher_id)};

  // For each philosopher, the convention is to initially pick up their left
  // chopstick, followed by the right one.
  auto left_index{philosopher_index % kPhilosopherCount};
  auto right_index{(philosopher_index + 1 + kPhilosopherCount) %
                   kPhilosopherCount};

  // To ensure the creation of an acyclic graph, the first philosopher holds
  // both chopsticks, while the last one holds none.
  auto has_left_chopstick{philosopher_index != kPhilosopherCount - 1};
  auto has_right_chopstick{philosopher_index == 0};

  philosopher.Materialize(
      philosopher_id, {&chopsticks_[left_index], &chopsticks_[right_index]},
      {&philosophers_[left_index], &philosophers_[right_index]},
      has_left_chopstick, has_right_chopstick);

  while (is_partying_.load()) {
    philosopher.Think();
    philosopher.GetHungry();
    philosopher.Eat();
  }
}

std::unique_ptr<DiningParty> GenerateDiningParty() {
  return std::make_unique<ChandraMisraDiningParty>();
}
}  // namespace dpp
