#include <time/TimerManager.hpp>

namespace framework::time {
  TimerManager::TimerManager(boost::asio::io_context& io_context, std::shared_ptr<iface::ITimerTask> task,
                             const std::chrono::milliseconds interval) :
    ioContext_(io_context), task_(std::move(task)), timer_(io_context), interval_(interval) {
    start();
  }

  auto TimerManager::start() -> void {
    schedule_next();
  }

  auto TimerManager::schedule_next() -> void {
    timer_.expires_after(interval_);
    timer_.async_wait(
      [this](const boost::system::error_code& ec)
      {
        if (!ec) {
          task_->execute();
          schedule_next();
        }
      });
  }
} // namespace framework::time
