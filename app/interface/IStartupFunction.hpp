#pragma once

namespace app
{
    class IStartupFunction
    {
    public:
        IStartupFunction() = default;
        virtual ~IStartupFunction() = default;
        virtual bool operator()() =0;
    };
}
