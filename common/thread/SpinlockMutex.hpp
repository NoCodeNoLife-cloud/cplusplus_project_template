#pragma once
#include <atomic>
#include <thread>

namespace common::thread {
/// \brief A simple spinlock mutex.
/// \details This class is a simple, lock-free spinlock mutex.
/// It is designed to be used in situations where a critical section of code is very short, such as when accessing a
/// shared resource. Because it is based on a spinlock, it will burn CPU cycles if it can't acquire the lock
/// immediately.
class SpinlockMutex {
public:
  SpinlockMutex() = default;

  /// \brief Acquires the spinlock, blocking if necessary until it becomes
  /// available.
  /// \details Continuously attempts to set the atomic flag. If the flag is
  /// already set, the thread yields to allow other thread to proceed.
  auto lock() -> void {
    while (flag_.test_and_set(std::memory_order_acquire)) {
      std::this_thread::yield();
    }
  }

  /// \brief Releases the spinlock.
  /// \details If there are thread waiting for the spinlock to become available,
  /// one of them will be unblocked.
  auto unlock() -> void {
    flag_.clear(std::memory_order_release);
  }

private:
  std::atomic_flag flag_;
};
}
