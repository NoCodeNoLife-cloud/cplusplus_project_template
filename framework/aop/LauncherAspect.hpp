#pragma once
#include "interface/IAop.hpp"
#include "time/FunctionProfiler.hpp"

namespace framework::aop {
  class LauncherAspect final : public iface::IAop<LauncherAspect> {
  public:
    explicit LauncherAspect();

  private:
    time::FunctionProfiler timer_;

    auto onEntry() -> void override;
    auto onExit() -> void override;
  };
} // namespace framework::aop
