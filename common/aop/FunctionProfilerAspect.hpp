#pragma once
#include <string>

#include "interface/IAop.hpp"
#include "utils/time/FunctionProfiler.hpp"

namespace fox {
/// @brief This class is an aspect for profiling function execution time.
/// It implements the IAop interface to provide entry and exit points
/// for measuring the duration of function calls.
class FunctionProfilerAspect final : public IAop<FunctionProfilerAspect> {
 public:
  explicit FunctionProfilerAspect(std::string function_name) : timer_(std::move(function_name), false) {}

  /// @brief Entry point
  auto onEntry() -> void override { timer_.recordStart(); }

  /// @brief Exit point
  auto onExit() -> void override { timer_.recordEnd(true); }

 private:
  FunctionProfiler timer_;
  std::string function_name_;
};
}  // namespace fox
