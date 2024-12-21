#pragma once
#include <string>

namespace common
{
    class UuidGenerator abstract
    {
    public:
        static auto GenerateRandomUuid() -> std::string;
    };
}
