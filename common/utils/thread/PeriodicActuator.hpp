#pragma once
#include <chrono>
#include <memory>
#include <boost/asio.hpp>

#include "interface/ITimerTask.hpp"

namespace common
{
    class PeriodicActuator
    {
    public:
        explicit PeriodicActuator(std::shared_ptr<ITimerTask> task, const std::chrono::milliseconds interval);
        auto start() -> void;

    private:
        boost::asio::io_context ioContext_;
        std::shared_ptr<ITimerTask> task_;
        boost::asio::steady_timer timer_;
        std::chrono::milliseconds interval_;
        auto scheduleNext() -> void;
    };
}
