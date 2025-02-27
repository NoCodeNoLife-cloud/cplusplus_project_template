#pragma once
#include <iostream>
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
        static auto mainTask() -> int;
        static auto initLogging() -> void;
        auto initStartTime() -> void;
        auto getRunTime() -> void;
        static auto finishMain() -> void;
    };

    inline auto Application::start() -> void
    {
        initLogging();
        initStartTime();
        try
        {
            mainTask();
        }
        catch (std::exception& e)
        {
            LOG(ERROR) << e.what();
        }
        getRunTime();
        finishMain();
    }

    inline auto Application::mainTask() -> int
    {
        return EXIT_SUCCESS;
    }

    inline auto Application::initLogging() -> void
    {
        google::InitGoogleLogging("main");
        FLAGS_logtostdout = true;
    }

    inline auto Application::initStartTime() -> void
    {
        start_ = std::chrono::high_resolution_clock::now();
    }

    inline auto Application::getRunTime() -> void
    {
        end_ = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double> duration = end_ - start_;
        LOG(INFO) << "program run time: " << duration.count() << " s" << std::endl;
    }

    inline auto Application::finishMain() -> void
    {
        google::ShutdownGoogleLogging();
    }
}
