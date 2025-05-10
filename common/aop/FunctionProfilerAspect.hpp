#pragma once
#include <aop/interface/IAop.hpp>
#include <time/FunctionProfiler.hpp>

namespace common {
  class FunctionProfilerAspect final : public IAop<FunctionProfilerAspect> {
  public:
    explicit FunctionProfilerAspect(std::string function_name);
    inline void onEntry() override;
    inline void onExit() override;

  private:
    FunctionProfiler timer_;
    std::string function_name_;
  };
}
