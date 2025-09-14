#pragma once
#include <atomic>
#include <thread>

namespace fox
{
/// @brief A spinlock mutex implementation using atomic_flag for synchronization.
/// This class provides a simple and efficient synchronization mechanism
/// suitable for protecting small critical sections where the lock is held
/// for a short duration.
class SpinlockMutex
{
  public:
    SpinlockMutex() = default;

    /// @brief Locks the spinlock, blocking until the lock is acquired.
    auto lock() -> void
    {
        while (flag_.test_and_set(std::memory_order_acquire))
        {
            std::this_thread::yield();
        }
    }

    /// @brief Unlocks the spinlock, allowing other threads to acquire it.
    auto unlock() -> void
    {
        flag_.clear(std::memory_order_release);
    }

  private:
    std::atomic_flag flag_;
};
} // namespace fox