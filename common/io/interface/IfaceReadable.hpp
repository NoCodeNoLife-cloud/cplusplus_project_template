#pragma once
namespace common::iface
{
    class IfaceReadable abstract
    {
    public:
        virtual ~IfaceReadable() = default;
        virtual auto read() -> int = 0;
    };
}
