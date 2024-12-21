#pragma once
namespace common
{
    class ICloseable abstract
    {
    public:
        virtual ~ICloseable() = default;
        virtual auto close() -> void = 0;
    };
}
