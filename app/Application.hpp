#pragma once
#include <glog/logging.h>

namespace app
{
    class Application
    {
    public:
        auto start() -> void;
    private:
        std::chrono::time_point<std::chrono::steady_clock> start_;
        std::chrono::time_point<std::chrono::steady_clock> end_;
        static auto mainTask() -> int32_t;
        static auto initLogging() -> void;
        auto initStartTime() -> void;
        auto getRunTime() -> void;
        static auto finishMain() -> void;
    };
}
