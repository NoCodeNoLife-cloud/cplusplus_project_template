#include "FunctionProfiler.hpp"

#include <glog/logging.h>

#include <iomanip>
#include <iostream>
#include <utility>

namespace common {
FunctionProfiler::FunctionProfiler(std::string function_name, const bool autoStart) : function_name_(std::move(function_name)) {
  if (autoStart) {
    recordStart();
  }
}

auto FunctionProfiler::recordStart() -> void { start_ = std::chrono::high_resolution_clock::now(); }

auto FunctionProfiler::getRunTime() const -> void {
  const std::chrono::duration<double, std::milli> duration_ms = end_ - start_;
  LOG(INFO) << function_name_ << " finish in " << std::fixed << std::setprecision(3) << duration_ms.count() / 1000.0 << " s";
}

auto FunctionProfiler::recordEnd(const bool autoPrint) -> void {
  end_ = std::chrono::high_resolution_clock::now();
  if (autoPrint) {
    getRunTime();
  }
}
}  // namespace common
