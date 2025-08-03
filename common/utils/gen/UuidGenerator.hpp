#pragma once
#include <string>

namespace common {
class UuidGenerator abstract {
 public:
  /// @brief Generates a random UUID string.
  /// @return A string representation of the generated UUID.
  static auto GenerateRandomUuid() -> std::string;
};
}  // namespace common
