#pragma once
#include <boost/asio.hpp>
#include <chrono>
#include <memory>

#include "interface/ITimerTask.hpp"

namespace fox
{
/// @brief A utility class that executes a given task periodically using Boost.Asio.
/// @details This class uses a steady_timer from Boost.Asio to schedule and execute tasks at regular intervals.
///          The task to be executed must implement the ITimerTask interface.
class PeriodicActuator
{
  public:
    explicit PeriodicActuator(std::shared_ptr<ITimerTask> task, std::chrono::milliseconds interval)
        : task_(std::move(task)), timer_(ioContext_), interval_(interval)
    {
    }

    /// @brief Start the periodic actuator to begin executing the task at specified intervals.
    /// @details This function initializes the timer and starts the first execution of the task.
    ///          The task will then be rescheduled automatically based on the configured interval.
    auto start() -> void
    {
        scheduleNext();
        ioContext_.run();
    }

  private:
    boost::asio::io_context ioContext_;
    std::shared_ptr<ITimerTask> task_;
    boost::asio::steady_timer timer_;
    std::chrono::milliseconds interval_;

    auto scheduleNext() -> void
    {
        timer_.expires_after(interval_);
        timer_.async_wait([this](const boost::system::error_code &ec) {
            if (!ec)
            {
                task_->execute();
                scheduleNext();
            }
        });
    }
};
} // namespace fox