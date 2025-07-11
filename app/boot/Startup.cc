#include <boot/Startup.hpp>
#include <service/log/GLogConfigurator.hpp>

namespace coco
{
    Startup::Startup()
    {
        registerTask();
        runAll();
    }

    auto Startup::registerTask() -> void
    {
        startup_tasks_.push_back(std::move(std::make_unique<GLogConfigurator>()));
    }

    auto Startup::runAll() const -> void
    {
        for (const auto& task : startup_tasks_)
        {
            task->run();
        }
    }
}
