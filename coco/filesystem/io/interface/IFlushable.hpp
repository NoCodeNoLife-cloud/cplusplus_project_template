#pragma once
namespace coco
{
    class IFlushable abstract
    {
    public:
        virtual ~IFlushable() = default;
        virtual auto flush() -> void = 0;
    };
}
