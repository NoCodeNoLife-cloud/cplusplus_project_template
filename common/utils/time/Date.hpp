#pragma once
#include <chrono>
#include <string>

namespace common {
class Date {
 public:
  Date();
  Date(int32_t year, int32_t month, int32_t day);
  Date(int32_t year, int32_t month, int32_t day, int32_t hours, int32_t minutes, int32_t seconds);
  explicit Date(int64_t timestamp);
  ~Date() = default;

  /// @brief Creates and returns a copy of this object.
  [[nodiscard]] auto clone() const -> Date;

  /// @brief Compares this date to the specified date.
  [[nodiscard]] auto equals(const Date& other) const -> bool;

  /// @brief Tests if this date is after the specified date.
  [[nodiscard]] auto after(const Date& other) const -> bool;

  /// @brief Tests if this date is before the specified date.
  [[nodiscard]] auto before(const Date& other) const -> bool;

  /// @brief Returns the number of milliseconds since January 1, 1970, 00:00:00 GMT.
  [[nodiscard]] auto getTime() const -> int64_t;

  /// @brief Returns the year represented by this date.
  [[nodiscard]] auto getYear() const -> int32_t;

  /// @brief Returns the month represented by this date.
  [[nodiscard]] auto getMonth() const -> int32_t;

  /// @brief Returns the day of the month represented by this date.
  [[nodiscard]] auto getDay() const -> int32_t;

  /// @brief Converts this date to a string representation.
  [[nodiscard]] auto toString() const -> std::string;

  /// @brief Returns a hash code value for this date.
  [[nodiscard]] auto hashCode() const -> size_t;

 private:
  std::chrono::system_clock::time_point time_point_;

  /// @brief Converts the time point to a std::tm structure.
  [[nodiscard]] auto toTm() const -> std::tm;
};
}  // namespace common
