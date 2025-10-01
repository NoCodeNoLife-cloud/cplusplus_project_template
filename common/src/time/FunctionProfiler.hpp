#pragma once

#include <chrono>
#include <string>

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
        /// @return The duration in milliseconds as a double, or -1.0 if timing data is incomplete.
        [[nodiscard]] auto getRunTimeMs() const -> double;

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> start_{};
        std::chrono::time_point<std::chrono::high_resolution_clock> end_{};
        std::string function_name_{};
        bool started_{false};
        bool ended_{false};
    };
}
