#include "src/time/FunctionProfiler.hpp"

#include <glog/logging.h>

#include <chrono>
#include <iomanip>
#include <string>
#include <utility>

namespace common
{
    FunctionProfiler::FunctionProfiler(std::string function_name,
                                       const bool autoStart) noexcept
        : function_name_(std::move(function_name))
    {
        if (autoStart)
        {
            recordStart();
        }
    }

    auto FunctionProfiler::recordStart() noexcept
        -> void
    {
        start_ = std::chrono::high_resolution_clock::now();
        started_ = true;
    }

    auto FunctionProfiler::recordEnd(const bool autoPrint) noexcept
        -> void
    {
        end_ = std::chrono::high_resolution_clock::now();
        ended_ = true;
        if (autoPrint)
        {
            getRunTime();
        }
    }

    auto FunctionProfiler::getRunTime() const
        -> void
    {
        if (!started_ || !ended_)
        {
            LOG(WARNING) << function_name_ << " timing data is incomplete. "
                << "Started: " << started_ << ", Ended: " << ended_;
            return;
        }

        const std::chrono::duration<double, std::milli> duration_ms = end_ - start_;
        LOG(INFO) << function_name_ << " finish in " << std::fixed << std::setprecision(3)
            << duration_ms.count() / 1000.0 << " s";
    }

    auto FunctionProfiler::getRunTimeMs() const
        -> double
    {
        if (!started_ || !ended_)
        {
            LOG(WARNING) << function_name_ << " timing data is incomplete. "
                << "Started: " << started_ << ", Ended: " << ended_;
            return -1.0;
        }

        const std::chrono::duration<double, std::milli> duration_ms = end_ - start_;
        return duration_ms.count();
    }
}
