#pragma once
#include <chrono>
#include <string>

namespace fox {
/// @brief Utility class for time-related operations
class Clock {
 public:
  /// @brief Get current date and time as a string
  static auto getCurrentDateTimeString() -> std::string;

  /// @brief Get current date and time as a compressed string
  static auto getCompressedCurrentDateTimeString() -> std::string;
};
}  // namespace fox
