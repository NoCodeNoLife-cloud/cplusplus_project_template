#include "PeriodicActuator.hpp"

namespace fox {
PeriodicActuator::PeriodicActuator(std::shared_ptr<ITimerTask> task, const std::chrono::milliseconds interval) : task_(std::move(task)), timer_(ioContext_), interval_(interval) {}

auto PeriodicActuator::start() -> void {
  scheduleNext();
  ioContext_.run();
}

auto PeriodicActuator::scheduleNext() -> void {
  timer_.expires_after(interval_);
  timer_.async_wait([this](const boost::system::error_code& ec) {
    if (!ec) {
      task_->execute();
      scheduleNext();
    }
  });
}
}  // namespace fox
