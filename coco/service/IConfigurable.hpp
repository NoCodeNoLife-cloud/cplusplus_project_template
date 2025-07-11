#pragma once
namespace coco
{
    class IConfigurable abstract
    {
    public:
        virtual ~IConfigurable() = default;

    private:
        [[nodiscard]] virtual auto doConfig() -> bool = 0;
    };
}
