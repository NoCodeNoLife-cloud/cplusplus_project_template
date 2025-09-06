#pragma once
#include <atomic>

namespace fox {
/// @brief A spinlock mutex implementation using atomic_flag for synchronization.
/// This class provides a simple and efficient synchronization mechanism
/// suitable for protecting small critical sections where the lock is held
/// for a short duration.
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
}  // namespace fox
