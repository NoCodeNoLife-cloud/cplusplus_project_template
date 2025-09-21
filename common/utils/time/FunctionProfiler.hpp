#pragma once
#include <glog/logging.h>

#include <chrono>
#include <iomanip>
#include <string>
#include <utility>

namespace fox
{
    /// @brief A utility class for profiling function execution time.
    /// @details This class provides functionality to measure and print the execution time
    /// of a function. It records the start and end times, and calculates the
    /// duration between them. The profiler can be used to measure performance
    /// of specific code sections.
    class FunctionProfiler
    {
    public:
        /// @brief Construct a FunctionProfiler with the specified function name.
        /// @param function_name The name of the function or code section being profiled.
        /// @param autoStart If true, automatically start timing upon construction.
        explicit FunctionProfiler(std::string function_name, bool autoStart = false) noexcept;

        /// @brief Records the start time of the function execution.
        /// @details Captures the current time as the start time for profiling.
        auto recordStart() noexcept -> void;

        /// @brief Records the end time of the function execution.
        /// @details Captures the current time as the end time for profiling.
        /// @param autoPrint If true, automatically prints the runtime.
        auto recordEnd(bool autoPrint = false) noexcept -> void;

        /// @brief Gets and prints the runtime of the function execution.
        /// @details Calculates the duration between start and end times and logs it.
        auto getRunTime() const -> void;

        /// @brief Gets the runtime duration in milliseconds.
        /// @details Calculates the duration between start and end times.
        /// @return The duration in milliseconds as a double.
        [[nodiscard]] auto getRunTimeMs() const -> double;

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> start_;
        std::chrono::time_point<std::chrono::high_resolution_clock> end_;
        std::string function_name_;
        bool started_{false};
        bool ended_{false};
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
        started_ = true;
    }

    inline auto FunctionProfiler::recordEnd(const bool autoPrint) noexcept -> void
    {
        end_ = std::chrono::high_resolution_clock::now();
        ended_ = true;
        if (autoPrint)
        {
            getRunTime();
        }
    }

    inline auto FunctionProfiler::getRunTime() const -> void
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

    inline auto FunctionProfiler::getRunTimeMs() const -> double
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
} // namespace fox
