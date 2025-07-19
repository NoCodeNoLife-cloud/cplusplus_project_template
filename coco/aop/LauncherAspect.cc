#include "LauncherAspect.hpp"

#include "boot/AppFactory.hpp"
#include "service/log/GLogConfigurator.hpp"
#include "type/util/ObjectFactory.hpp"

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
        startup_tasks_.push_back(std::move(std::make_unique<app::AppFactory>()));
    }

    auto LauncherAspect::runAll() const -> void
    {
        for (const auto& task : startup_tasks_)
        {
            task->execute();
        }
    }
}
