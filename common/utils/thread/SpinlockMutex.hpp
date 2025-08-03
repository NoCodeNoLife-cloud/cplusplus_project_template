#pragma once
#include <atomic>

namespace common {
class SpinlockMutex {
 public:
  SpinlockMutex();

  /// @brief Locks the spinlock, blocking until the lock is acquired.
  auto lock() -> void;

  /// @brief Unlocks the spinlock, allowing other threads to acquire it.
  auto unlock() -> void;

 private:
  std::atomic_flag flag_;
};
}  // namespace common
