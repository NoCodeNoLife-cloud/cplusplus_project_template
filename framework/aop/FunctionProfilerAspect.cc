#include <aop/FunctionProfilerAspect.hpp>
#include <utility>

namespace framework::aop {
  FunctionProfilerAspect::FunctionProfilerAspect(std::string function_name) : timer_(std::move(function_name), false) {}

  void FunctionProfilerAspect::onEntry() {
    timer_.recordStart();
  }

  void FunctionProfilerAspect::onExit() {
    timer_.recordEnd(true);
  }
}
