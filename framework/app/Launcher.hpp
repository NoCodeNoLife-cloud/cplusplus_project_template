#pragma once
#include <glog/logging.h>

namespace framework::app {
    class Launcher
    {
    public:
        Launcher();

        ~Launcher();

    private:
        static constexpr bool LOG_TO_STDOUT{true};
        inline static const std::string LOG_NAME{"main"};
        static constexpr bool COLOR_LOG_TO_STDERR{true};
        static constexpr int32_t MIN_LOG_LEVEL{0};
        std::chrono::time_point<std::chrono::steady_clock> start_;
        std::chrono::time_point<std::chrono::steady_clock> end_;

        auto start() -> void;

        auto finish() -> void;

        static auto initLogging() -> void;

        auto initStartTime() -> void;

        auto getRunTime() -> void;
    };
} // namespace framework::app
