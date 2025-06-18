#pragma once
#include <memory>
#include <vector>
#include <interface/IStartupTask.hpp>

namespace common
{
    class Startup
    {
    public:
        Startup();

    private:
        std::vector<std::unique_ptr<app::IStartupTask>> startup_tasks_;
        auto registerTask() -> void;
        auto runAll() const -> void;
    };
}
