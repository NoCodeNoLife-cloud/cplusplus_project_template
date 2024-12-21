#pragma once
#include <string>

#include "interface/IAop.hpp"
#include "utils/time/FunctionProfiler.hpp"

namespace common
{
    class FunctionProfilerAspect final : public IAop<FunctionProfilerAspect>
    {
    public:
        explicit FunctionProfilerAspect(std::string function_name);
        inline void onEntry() override;
        inline void onExit() override;

    private:
        FunctionProfiler timer_;
        std::string function_name_;
    };
}
