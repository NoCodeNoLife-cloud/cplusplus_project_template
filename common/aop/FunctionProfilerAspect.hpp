#pragma once
#include <string>

#include "interface/IAop.hpp"
#include "utils/time/FunctionProfiler.hpp"

namespace common {
class FunctionProfilerAspect final : public IAop<FunctionProfilerAspect> {
 public:
  explicit FunctionProfilerAspect(std::string function_name);

  /// @brief Entry point
  inline auto onEntry() -> void override;

  /// @brief Exit point
  inline auto onExit() -> void override;

 private:
  FunctionProfiler timer_;
  std::string function_name_;
};
}  // namespace common
