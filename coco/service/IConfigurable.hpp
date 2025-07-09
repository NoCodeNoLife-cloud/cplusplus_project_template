#pragma once
namespace coco
{
    class IConfigurable abstract
    {
    public:
        virtual ~IConfigurable() = default;
        [[nodiscard]] virtual auto doConfig() -> bool = 0;
    };
}
