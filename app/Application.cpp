#include "Application.hpp"
#include <iostream>

namespace app
{
    auto Application::mainTask() -> int32_t
    {
        return EXIT_SUCCESS;
    }

    auto Application::start() -> void
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

    auto Application::initLogging() -> void
    {
        google::InitGoogleLogging("main");
        FLAGS_logtostdout = true;
    }

    auto Application::initStartTime() -> void
    {
        start_ = std::chrono::high_resolution_clock::now();
    }

    auto Application::getRunTime() -> void
    {
        end_ = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double> duration = end_ - start_;
        LOG(INFO) << "program run time: " << duration.count() << " s" << std::endl;
    }

    auto Application::finishMain() -> void
    {
        google::ShutdownGoogleLogging();
    }
}

int32_t main([[maybe_unused]] int32_t argc, [[maybe_unused]] char* argv[])
{
    app::Application application;
    application.start();
}
