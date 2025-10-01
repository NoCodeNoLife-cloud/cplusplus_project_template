#include "src/aop/FunctionProfilerAspect.hpp"
#include <glog/logging.h>
#include <utility>

namespace fox
{
    FunctionProfilerAspect::FunctionProfilerAspect(std::string function_name) : profiler_(function_name, true), function_name_(std::move(function_name))
    {
    }

    auto FunctionProfilerAspect::onEntry() -> void
    {
        LOG(INFO) << "Entering function: " << function_name_;
    }

    auto FunctionProfilerAspect::onExit() -> void
    {
        profiler_.recordEnd(true);
        LOG(INFO) << "Exiting function: " << function_name_;
    }

    auto FunctionProfilerAspect::onException() -> void
    {
        profiler_.recordEnd(true);
        LOG(INFO) << "Function exited with exception: " << function_name_;
    }
}
