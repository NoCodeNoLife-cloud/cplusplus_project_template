#pragma once
#include <boost/asio.hpp>
#include <memory>
#include <chrono>
#include "interface/IfaceTimerTask.hpp"

namespace common::time {
/// \brief Class TimerManager
/// \details This class is responsible for managing a timer that invokes a task at a specified interval.
/// The TimerManager class provides methods to start and stop the timer. When the start method is called, the timer is
/// started and the task is invoked at the specified interval. The stop method can be used to stop the timer and prevent
/// the task from being invoked any further.
/// The TimerManager class uses the boost::asio library to implement the timer functionality.
/// \remark The TimerManager class is not thread-safe. Synchronization is needed for concurrent access.
class TimerManager {
public:
  TimerManager(boost::asio::io_context& io_context, std::shared_ptr<iface::IfaceTimerTask> task, const std::chrono::milliseconds interval)
    : ioContext_(io_context), task_(std::move(task)), timer_(io_context), interval_(interval) {
    start();
  }

  /// \brief Starts the timer.
  /// \details Starts the timer and schedules the first timer event. The timer event will cause the task to be invoked.
  /// \remark The timer will not be started if it is already running.
  auto start() -> void {
    schedule_next();
  }

private:
  boost::asio::io_context& ioContext_;
  std::shared_ptr<iface::IfaceTimerTask> task_;
  boost::asio::steady_timer timer_;
  std::chrono::milliseconds interval_;
  /// \brief Schedules the next timer event.
  /// \details Schedules the next timer event using the interval specified in the constructor.
  /// When the timer event is triggered, the task is invoked.
  auto schedule_next() -> void {
    timer_.expires_after(interval_);
    timer_.async_wait([this](const boost::system::error_code& ec) {
      if (!ec) {
        task_->execute();
        schedule_next();
      }
    });
  }
};
}
