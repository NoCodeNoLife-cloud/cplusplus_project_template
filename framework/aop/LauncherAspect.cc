#include "LauncherAspect.hpp"

#include "log/GLogConfiguration.hpp"
#include "time/FunctionProfiler.hpp"

namespace framework::aop {

LauncherAspect::LauncherAspect() : timer_("program", true) {}

auto LauncherAspect::onEntry() -> void { const log::GLogConfiguration config{}; }

auto LauncherAspect::onExit() -> void { timer_.recordEnd(true); }

}  // namespace framework::aop
