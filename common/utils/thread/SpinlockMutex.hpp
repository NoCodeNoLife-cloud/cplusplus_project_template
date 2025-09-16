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
        /// @brief Default constructor initializes the spinlock in unlocked state.
        SpinlockMutex() noexcept;

        /// @brief Locks the spinlock, blocking until the lock is acquired.
        /// Uses test_and_set in a loop with yielding to reduce CPU usage.
        auto lock() noexcept -> void;

        /// @brief Unlocks the spinlock, allowing other threads to acquire it.
        /// Clears the atomic flag with release memory ordering.
        auto unlock() noexcept -> void;

    private:
        std::atomic_flag flag_ = ATOMIC_FLAG_INIT;
    };

    inline SpinlockMutex::SpinlockMutex() noexcept = default;

    inline auto SpinlockMutex::lock() noexcept -> void
    {
        while (flag_.test_and_set(std::memory_order_acquire))
        {
            std::this_thread::yield();
        }
    }

    inline auto SpinlockMutex::unlock() noexcept -> void
    {
        flag_.clear(std::memory_order_release);
    }
} // namespace fox
