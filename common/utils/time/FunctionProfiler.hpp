#pragma once
#include <chrono>

namespace common {
class FunctionProfiler {
 public:
  explicit FunctionProfiler(std::string function_name, bool autoStart = false);
  auto recordStart() -> void;
  auto recordEnd(bool autoPrint = false) -> void;
  auto getRunTime() const -> void;

 private:
  std::chrono::time_point<std::chrono::steady_clock> start_;
  std::chrono::time_point<std::chrono::steady_clock> end_;
  std::string function_name_;
};
}  // namespace common
