#pragma once
#include <chrono>
#include <string>

namespace framework::time
{
class Clock
{
  public:
    static auto getCurrentDateTimeString() -> std::string;
    static auto getCompressedCurrentDateTimeString() -> std::string;
};
} // namespace framework::time
