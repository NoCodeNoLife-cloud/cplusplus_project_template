#pragma once
#include <chrono>
#include <memory>
#include <boost/asio.hpp>
#include <time/interface/ITimerTask.hpp>

namespace common {
  class TimerManager {
  public:
    explicit TimerManager(boost::asio::io_context& io_context, std::shared_ptr<ITimerTask> task,
                          std::chrono::milliseconds interval);

    auto start() -> void;

  private:
    boost::asio::io_context& ioContext_;
    std::shared_ptr<ITimerTask> task_;
    boost::asio::steady_timer timer_;
    std::chrono::milliseconds interval_;

    auto schedule_next() -> void;
  };
}
