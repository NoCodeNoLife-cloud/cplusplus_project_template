#include "LauncherAspect.hpp"

#include "service/log/GLogConfigurator.hpp"

namespace coco
{
    LauncherAspect::LauncherAspect() : timer_("program", true)
    {
        registerTask();
        runAll();
    }

    auto LauncherAspect::onExit() -> void
    {
        timer_.recordEnd(true);
    }

    auto LauncherAspect::registerTask() -> void
    {
        startup_tasks_.push_back(std::move(std::make_unique<GLogConfigurator>()));
    }

    auto LauncherAspect::runAll() const -> void
    {
        for (const auto& task : startup_tasks_)
        {
            task->run();
        }
    }
}
