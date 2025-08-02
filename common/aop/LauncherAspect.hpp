#pragma once
#include "interface/IAop.hpp"
#include "interface/IStartupTask.hpp"
#include "utils/time/FunctionProfiler.hpp"

namespace common {
class LauncherAspect final : public IAop<LauncherAspect> {
 public:
  explicit LauncherAspect();

 private:
  FunctionProfiler timer_;
  std::vector<std::unique_ptr<service::IStartupTask>> startup_tasks_;

  /// @brief Exit point
  auto onExit() -> void override;

  /// @brief Entry point
  auto registerTask() -> void;

  /// @brief Run all tasks
  auto runAll() const -> void;
};
}  // namespace common
