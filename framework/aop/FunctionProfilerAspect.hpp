#pragma once
#include "interface/IAop.hpp"
#include "time/FunctionProfiler.hpp"

namespace framework::aop {
  class FunctionProfilerAspect final : public iface::IAop<FunctionProfilerAspect> {
  public:
    explicit FunctionProfilerAspect(std::string function_name);
    inline void onEntry() override;
    inline void onExit() override;

  private:
    time::FunctionProfiler timer_;
    std::string function_name_;
  };
} // namespace framework::aop
