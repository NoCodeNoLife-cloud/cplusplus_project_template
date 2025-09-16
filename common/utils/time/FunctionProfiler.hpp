#pragma once
#include <glog/logging.h>

#include <chrono>
#include <iomanip>
#include <string>
#include <utility>

namespace fox
{
    /// @brief A utility class for profiling function execution time.
    /// This class provides functionality to measure and print the execution time
    /// of a function. It records the start and end times, and calculates the
    /// duration between them.
    class FunctionProfiler
    {
    public:
        explicit FunctionProfiler(std::string function_name, bool autoStart = false) noexcept;

        /// @brief Records the start time of the function execution.
        auto recordStart() noexcept -> void;

        /// @brief Records the end time of the function execution.
        /// @param autoPrint If true, automatically prints the runtime.
        auto recordEnd(bool autoPrint = false) noexcept -> void;

        /// @brief Gets the runtime of the function execution.
        auto getRunTime() const -> void;

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> start_;
        std::chrono::time_point<std::chrono::high_resolution_clock> end_;
        std::string function_name_;
    };

    inline FunctionProfiler::FunctionProfiler(std::string function_name,
                                              const bool autoStart) noexcept : function_name_(std::move(function_name))
    {
        if (autoStart)
        {
            recordStart();
        }
    }

    inline auto FunctionProfiler::recordStart() noexcept -> void
    {
        start_ = std::chrono::high_resolution_clock::now();
    }

    inline auto FunctionProfiler::recordEnd(const bool autoPrint) noexcept -> void
    {
        end_ = std::chrono::high_resolution_clock::now();
        if (autoPrint)
        {
            getRunTime();
        }
    }

    inline auto FunctionProfiler::getRunTime() const -> void
    {
        const std::chrono::duration<double, std::milli> duration_ms = end_ - start_;
        LOG(INFO) << function_name_ << " finish in " << std::fixed << std::setprecision(3)
            << duration_ms.count() / 1000.0 << " s";
    }
} // namespace fox
