#pragma once
namespace common::iface
{
    class IFlushable abstract
    {
    public:
        virtual ~IFlushable() = default;
        virtual auto flush() -> void = 0;
    };
}
