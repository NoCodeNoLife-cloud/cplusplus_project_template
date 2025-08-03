#pragma once
#include <chrono>

namespace common {
class FunctionProfiler {
 public:
  explicit FunctionProfiler(std::string function_name, bool autoStart = false);

  /// @brief Records the start time of the function execution.
  auto recordStart() -> void;

  /// @brief Records the end time of the function execution.
  /// @param autoPrint If true, automatically prints the runtime.
  auto recordEnd(bool autoPrint = false) -> void;

  /// @brief Gets the runtime of the function execution.
  auto getRunTime() const -> void;

 private:
  std::chrono::time_point<std::chrono::steady_clock> start_;
  std::chrono::time_point<std::chrono::steady_clock> end_;
  std::string function_name_;
};
}  // namespace common
