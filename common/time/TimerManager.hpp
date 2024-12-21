#pragma once
#include <boost/asio.hpp>
#include <memory>
#include <chrono>
#include "interface/IfaceTimerTask.hpp"

namespace common::time
{
    class TimerManager
    {
    public:
        TimerManager(boost::asio::io_context& io_context, std::shared_ptr<iface::IfaceTimerTask> task, const std::chrono::milliseconds interval): ioContext_(io_context), task_(std::move(task)), timer_(io_context), interval_(interval)
        {
            start();
        }

        auto start() -> void
        {
            schedule_next();
        }

    private:
        boost::asio::io_context& ioContext_;
        std::shared_ptr<iface::IfaceTimerTask> task_;
        boost::asio::steady_timer timer_;
        std::chrono::milliseconds interval_;

        auto schedule_next() -> void
        {
            timer_.expires_after(interval_);
            timer_.async_wait([this](const boost::system::error_code& ec)
            {
                if (!ec)
                {
                    task_->execute();
                    schedule_next();
                }
            });
        }
    };
}
