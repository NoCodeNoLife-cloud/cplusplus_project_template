#pragma once
namespace common::iface
{
    class ICloseable abstract
    {
    public:
        virtual ~ICloseable() = default;
        virtual auto close() -> void = 0;
    };
}
