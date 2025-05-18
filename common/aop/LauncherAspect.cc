#include <aop/LauncherAspect.hpp>
#include <service/log/GLogConfig.hpp>
#include <time/FunctionProfiler.hpp>

namespace common {
  LauncherAspect::LauncherAspect() : timer_("program", true) {}

  auto LauncherAspect::onEntry() -> void {
    const GLogConfig config{};
  }

  auto LauncherAspect::onExit() -> void {
    timer_.recordEnd(true);
  }
}
