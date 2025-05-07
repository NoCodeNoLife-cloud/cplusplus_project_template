#pragma once
#include <aop/interface/IAop.hpp>
#include <time/FunctionProfiler.hpp>

namespace common {
  class LauncherAspect final : public IAop<LauncherAspect> {
  public:
    explicit LauncherAspect();

  private:
    FunctionProfiler timer_;
    auto onEntry() -> void override;
    auto onExit() -> void override;
  };
}
