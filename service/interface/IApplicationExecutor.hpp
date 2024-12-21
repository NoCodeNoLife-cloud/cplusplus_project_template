#pragma once
#include <cstdint>

namespace app
{
    class IApplicationExecutor abstract
    {
    public:
        virtual ~IApplicationExecutor() = default;
        [[nodiscard]] virtual auto execute(int32_t argc, char* argv[]) -> bool =0;
    };
}
