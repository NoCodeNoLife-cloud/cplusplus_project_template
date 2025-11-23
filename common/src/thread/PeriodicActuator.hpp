#pragma once
#include <boost/asio.hpp>
#include <chrono>
#include <memory>

#include "interface/ITimerTask.hpp"

namespace common
{
    /// @brief A utility class that executes a given task periodically using Boost.Asio.
    /// @details This class uses a steady_timer from Boost.Asio to schedule and execute tasks at regular intervals.
    ///          The task to be executed must implement the interface.
    class PeriodicActuator
    {
    public:
        /// @brief Construct a PeriodicActuator with a task and interval
        /// @param task The task to execute periodically
        /// @param interval The interval between executions
        // ReSharper disable once CppDFATimeOver
        explicit PeriodicActuator(std::shared_ptr<ITimerTask> task,
                                  std::chrono::milliseconds interval) noexcept;

        /// @brief Start the periodic actuator to begin executing the task at specified intervals.
        /// @details This function initializes the timer and starts the first execution of the task.
        ///          The task will then be rescheduled automatically based on the configured interval.
        auto start()
            -> void;

    private:
        boost::asio::io_context ioContext_{};
        std::shared_ptr<ITimerTask> task_{};
        boost::asio::steady_timer timer_;
        std::chrono::milliseconds interval_{};

        /// @brief Schedule the next execution of the task
        auto scheduleNext()
            -> void;
    };
}
