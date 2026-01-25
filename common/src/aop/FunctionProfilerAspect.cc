#include "src/aop/FunctionProfilerAspect.hpp"
#include <utility>

namespace common::aop {
    FunctionProfilerAspect::FunctionProfilerAspect(std::string function_name)
        : profiler_(function_name, true), function_name_(std::move(function_name)) {
    }

    auto FunctionProfilerAspect::onEntry() -> void {
    }

    auto FunctionProfilerAspect::onExit() -> void {
        profiler_.recordEnd(true);
    }

    auto FunctionProfilerAspect::onException(std::exception_ptr e) -> void {
        profiler_.recordEnd(true);
    }
}
