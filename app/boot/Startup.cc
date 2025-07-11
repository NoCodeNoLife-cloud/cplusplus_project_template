#include <AppConfigurator.hpp>
#include <boot/Startup.hpp>
#include <service/log/GLogConfigurator.hpp>

namespace app
{
    Startup::Startup()
    {
        registerTask();
        runAll();
    }

    auto Startup::registerTask() -> void
    {
        startup_tasks_.push_back(std::move(std::make_unique<coco::GLogConfigurator>()));
        startup_tasks_.push_back(std::move(std::make_unique<AppConfigurator>()));
    }

    auto Startup::runAll() const -> void
    {
        for (const auto& task : startup_tasks_)
        {
            task->run();
        }
    }
}
