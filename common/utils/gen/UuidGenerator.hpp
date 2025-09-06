#pragma once
#include <string>

namespace fox {
/// @brief A utility class for generating UUIDs.
/// This class provides functionality to generate random UUID strings.
class UuidGenerator {
 public:
  /// @brief Generates a random UUID string.
  /// @return A string representation of the generated UUID.
  static auto GenerateRandomUuid() -> std::string;
};
}  // namespace fox
