#pragma once
#include <string>

namespace common {
/// @brief A utility class for generating UUIDs.
/// This class provides functionality to generate random UUID strings.
class UuidGenerator abstract {
 public:
  /// @brief Generates a random UUID string.
  /// @return A string representation of the generated UUID.
  static auto GenerateRandomUuid() -> std::string;
};
}  // namespace common
