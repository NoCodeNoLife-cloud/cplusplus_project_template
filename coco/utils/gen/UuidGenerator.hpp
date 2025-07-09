#pragma once
#include <string>

namespace coco
{
    class UuidGenerator abstract
    {
    public:
        static auto GenerateRandomUuid() -> std::string;
    };
}
