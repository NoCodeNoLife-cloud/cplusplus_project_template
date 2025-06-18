#pragma once
#include <aop/interface/IAop.hpp>
#include <utils/time/FunctionProfiler.hpp>

namespace common
{
    class LauncherAspect final : public IAop<LauncherAspect>
    {
    public:
        explicit LauncherAspect();

    private:
        FunctionProfiler timer_;
        auto onExit() -> void override;
    };
}
