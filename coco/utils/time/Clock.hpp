#pragma once
#include <chrono>
#include <string>

namespace coco
{
    class Clock
    {
    public:
        static auto getCurrentDateTimeString() -> std::string;
        static auto getCompressedCurrentDateTimeString() -> std::string;
    };
}
