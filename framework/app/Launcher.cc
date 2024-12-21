#include "Launcher.hpp"
#include <iomanip>
#include <iostream>

namespace framework::app {
    Launcher::Launcher() { start(); }

    Launcher::~Launcher() { finish(); }

    auto Launcher::start() -> void {
        initLogging();
        initStartTime();
        getRunTime();
    }

    auto Launcher::initLogging() -> void {
        google::InitGoogleLogging(LOG_NAME.c_str());
        FLAGS_logtostdout = LOG_TO_STDOUT;
        FLAGS_colorlogtostderr = COLOR_LOG_TO_STDERR;
        FLAGS_minloglevel = MIN_LOG_LEVEL;
    }

    auto Launcher::initStartTime() -> void { start_ = std::chrono::high_resolution_clock::now(); }

    auto Launcher::getRunTime() -> void {
        end_ = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double, std::milli> duration_ms = end_ - start_;
        LOG(INFO) << "program finish in " << std::fixed << std::setprecision(3) << duration_ms.count() / 1000.0 << " s";
    }

    auto Launcher::finish() -> void {
        getRunTime();
        google::ShutdownGoogleLogging();
    }
} // namespace framework::app
