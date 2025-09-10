#pragma once
#include <glog/logging.h>

#include <chrono>
#include <iomanip>
#include <string>
#include <utility>

namespace fox {
/// @brief A utility class for profiling function execution time.
/// This class provides functionality to measure and print the execution time
/// of a function. It records the start and end times, and calculates the
/// duration between them.
class FunctionProfiler {
 public:
  explicit FunctionProfiler(std::string function_name, bool autoStart = false) : function_name_(std::move(function_name)) {
    if (autoStart) {
      recordStart();
    }
  }

  /// @brief Records the start time of the function execution.
  auto recordStart() -> void { start_ = std::chrono::high_resolution_clock::now(); }

  /// @brief Records the end time of the function execution.
  /// @param autoPrint If true, automatically prints the runtime.
  auto recordEnd(bool autoPrint = false) -> void {
    end_ = std::chrono::high_resolution_clock::now();
    if (autoPrint) {
      getRunTime();
    }
  }

  /// @brief Gets the runtime of the function execution.
  auto getRunTime() const -> void {
    const std::chrono::duration<double, std::milli> duration_ms = end_ - start_;
    LOG(INFO) << function_name_ << " finish in " << std::fixed << std::setprecision(3) << duration_ms.count() / 1000.0 << " s";
  }

 private:
  std::chrono::time_point<std::chrono::steady_clock> start_;
  std::chrono::time_point<std::chrono::steady_clock> end_;
  std::string function_name_;
};
}  // namespace fox