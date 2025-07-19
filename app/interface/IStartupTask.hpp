#pragma once

namespace app
{
    class IStartupTask abstract
    {
    public:
        virtual ~IStartupTask() = default;
        virtual auto execute() -> bool =0;
    };
}
