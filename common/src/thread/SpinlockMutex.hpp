#pragma once
#include <atomic>

namespace common
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
        auto lock() noexcept
            -> void;

        /// @brief Unlocks the spinlock, allowing other threads to acquire it.
        /// Clears the atomic flag with release memory ordering.
        auto unlock() noexcept
            -> void;

    private:
        std::atomic_flag flag_ = ATOMIC_FLAG_INIT;
    };
}
