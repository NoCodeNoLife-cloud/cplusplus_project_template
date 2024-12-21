#pragma once
#include <boost/asio.hpp>
#include <chrono>
#include <memory>

#include "interface/ITimerTask.hpp"

namespace framework::time
{

class TimerManager
{
  public:
    explicit TimerManager(boost::asio::io_context &io_context, std::shared_ptr<iface::ITimerTask> task, std::chrono::milliseconds interval);

    auto start() -> void;

  private:
    boost::asio::io_context &ioContext_;
    std::shared_ptr<iface::ITimerTask> task_;
    boost::asio::steady_timer timer_;
    std::chrono::milliseconds interval_;

    auto schedule_next() -> void;
};

} // namespace framework::time
