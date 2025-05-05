#pragma once
#include <string>

namespace framework::gen {
  class UuidGenerator abstract {
  public:
    static auto GenerateRandomUuid() -> std::string;
  };
} // namespace framework::gen
