#include <aop/LauncherAspect.hpp>
#include <log/GLogConfig.hpp>
#include <time/FunctionProfiler.hpp>

namespace framework::aop {
  LauncherAspect::LauncherAspect() : timer_("program", true) {}

  auto LauncherAspect::onEntry() -> void {
    const log::GLogConfig config{};
  }

  auto LauncherAspect::onExit() -> void {
    timer_.recordEnd(true);
  }
}
