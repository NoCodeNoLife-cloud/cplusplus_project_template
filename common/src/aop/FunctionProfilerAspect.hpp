#pragma once
#include <glog/logging.h>
#include <string>

#include "interface/IAop.hpp"
#include "utils/time/FunctionProfiler.hpp"

namespace fox
{
    /// @brief This class is an aspect for profiling function execution time.
    /// @details It implements the IAop interface to provide entry and exit points
    /// for measuring the duration of function calls. This aspect can be used
    /// with the AOP framework to automatically profile function execution.
    class FunctionProfilerAspect : public IAop<FunctionProfilerAspect>
    {
    public:
        /// @brief Construct a FunctionProfilerAspect with the given function name
        /// @param function_name The name of the function to profile
        explicit FunctionProfilerAspect(std::string function_name);

        /// @brief Entry point - records the start time of the function
        /// @details Called when entering the function to be profiled
        auto onEntry() -> void override;

        /// @brief Exit point - records the end time of the function and prints the result
        /// @details Called when exiting the function to be profiled
        auto onExit() -> void override;

        /// @brief Exception point - records the end time when exception occurs
        /// @details Called when function exits with exception
        auto onException() -> void;

    private:
        FunctionProfiler profiler_;
        std::string function_name_;
    };

    inline FunctionProfilerAspect::FunctionProfilerAspect(std::string function_name) : profiler_(function_name, true), function_name_(std::move(function_name))
    {
    }

    inline auto FunctionProfilerAspect::onEntry() -> void
    {
        LOG(INFO) << "Entering function: " << function_name_;
    }

    inline auto FunctionProfilerAspect::onExit() -> void
    {
        profiler_.recordEnd(true);
        LOG(INFO) << "Exiting function: " << function_name_;
    }

    inline auto FunctionProfilerAspect::onException() -> void
    {
        profiler_.recordEnd(true);
        LOG(INFO) << "Function exited with exception: " << function_name_;
    }
}
