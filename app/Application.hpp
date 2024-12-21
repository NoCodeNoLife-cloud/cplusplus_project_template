#pragma once
#include <iostream>
#include <glog/logging.h>

namespace app
{
    class Application
    {
    public:
        auto start() -> void
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

    private:
        std::chrono::time_point<std::chrono::steady_clock> start_;
        std::chrono::time_point<std::chrono::steady_clock> end_;

        static auto mainTask() -> int
        {
            return EXIT_SUCCESS;
        }

        static auto initLogging() -> void
        {
            google::InitGoogleLogging("main");
            FLAGS_logtostdout = true;
        }

        auto initStartTime() -> void
        {
            start_ = std::chrono::high_resolution_clock::now();
        }

        auto getRunTime() -> void
        {
            end_ = std::chrono::high_resolution_clock::now();
            const std::chrono::duration<double> duration = end_ - start_;
            LOG(INFO) << "program run time: " << duration.count() << " s" << std::endl;
        }

        static auto finishMain() -> void
        {
            google::ShutdownGoogleLogging();
        }
    };
}
