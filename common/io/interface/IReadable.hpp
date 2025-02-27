#pragma once
namespace common::iface
{
    class IReadable abstract
    {
    public:
        virtual ~IReadable() = default;
        virtual auto read() -> int = 0;
    };
}
