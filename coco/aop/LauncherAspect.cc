#include <aop/LauncherAspect.hpp>
#include <utils/time/FunctionProfiler.hpp>

namespace coco
{
    LauncherAspect::LauncherAspect() : timer_("program", true)
    {
    }

    auto LauncherAspect::onExit() -> void
    {
        timer_.recordEnd(true);
    }
}
