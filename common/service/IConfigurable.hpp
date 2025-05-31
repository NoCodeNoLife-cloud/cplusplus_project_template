#pragma once
namespace common
{
    class IConfigurable abstract
    {
    public:
        virtual ~IConfigurable() = default;
        [[nodiscard]] virtual auto doConfig() -> bool = 0;
    };
}
