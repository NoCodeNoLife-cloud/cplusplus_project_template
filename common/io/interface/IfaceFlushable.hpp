#pragma once
namespace common::iface
{
    class IfaceFlushable abstract
    {
    public:
        virtual ~IfaceFlushable() = default;
        virtual auto flush() -> void = 0;
    };
}
