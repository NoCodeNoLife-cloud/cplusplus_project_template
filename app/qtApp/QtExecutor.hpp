#pragma once
#include "interface/IApplicationExecutor.hpp"

namespace app
{
    class QtExecutor final : public IApplicationExecutor
    {
    public:
        [[nodiscard]] auto execute(int32_t argc, char* argv[]) -> bool override;
    };
}
