#pragma once
namespace coco
{
    class IReadable abstract
    {
    public:
        virtual ~IReadable() = default;
        virtual auto read() -> int32_t = 0;
    };
}
