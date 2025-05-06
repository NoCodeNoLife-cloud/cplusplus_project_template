#pragma once
#include <string>

namespace framework {
  class UuidGenerator abstract {
  public:
    static auto GenerateRandomUuid() -> std::string;
  };
}
