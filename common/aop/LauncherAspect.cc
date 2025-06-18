#include <aop/LauncherAspect.hpp>
#include <service/log/GLogConfig.hpp>
#include <utils/time/FunctionProfiler.hpp>

namespace common
{
    LauncherAspect::LauncherAspect() : timer_("program", true)
    {
    }

    auto LauncherAspect::onExit() -> void
    {
        timer_.recordEnd(true);
    }
}
