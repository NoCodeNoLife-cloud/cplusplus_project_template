#pragma once
#include <string>

#include "interface/IAop.hpp"
#include "utils/time/FunctionProfiler.hpp"

namespace fox
{
    /// @brief This class is an aspect for profiling function execution time.
    /// It implements the IAop interface to provide entry and exit points
    /// for measuring the duration of function calls.
    class FunctionProfilerAspect final : public IAop<FunctionProfilerAspect>
    {
    public:
        /// @brief Construct a FunctionProfilerAspect with the given function name
        /// @param function_name The name of the function to profile
        explicit FunctionProfilerAspect(std::string function_name);

        /// @brief Entry point - records the start time of the function
        auto onEntry() -> void override;

        /// @brief Exit point - records the end time of the function and prints the result
        auto onExit() -> void override;

    private:
        FunctionProfiler timer_;
    };

    inline FunctionProfilerAspect::FunctionProfilerAspect(std::string function_name)
        : timer_(std::move(function_name), false)
    {
    }

    inline auto FunctionProfilerAspect::onEntry() -> void
    {
        timer_.recordStart();
    }

    inline auto FunctionProfilerAspect::onExit() -> void
    {
        timer_.recordEnd(true);
    }
} // namespace fox
