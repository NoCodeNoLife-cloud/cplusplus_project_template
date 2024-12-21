#pragma once
namespace common::iface
{
    class IfaceCloseable abstract
    {
    public:
        virtual ~IfaceCloseable() = default;
        virtual auto close() -> void = 0;
    };
}
