#include <thread/TimerManager.hpp>

namespace common
{
    TimerManager::TimerManager(std::shared_ptr<ITimerTask> task, const std::chrono::milliseconds interval): task_(std::move(task)), timer_(ioContext_), interval_(interval)
    {
    }

    auto TimerManager::start() -> void
    {
        schedule_next();
        ioContext_.run();
    }

    auto TimerManager::schedule_next() -> void
    {
        timer_.expires_after(interval_);
        timer_.async_wait(
            [this](const boost::system::error_code& ec)
            {
                if (!ec)
                {
                    task_->execute();
                    schedule_next();
                }
            });
    }
}
