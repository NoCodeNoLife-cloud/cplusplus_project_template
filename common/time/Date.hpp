#pragma once
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>

namespace common::io {
/// \brief Class representing a date-time object.
/// \details The class provides a way to represent a date-time object. It provides
/// methods to retrieve the year, month, day, hour, minute and second components
/// of the date, as well as methods to compare two date objects. The class also
/// provides a method to get the current date-time object from the system clock.
class Date {
public:
  ~Date() = default;

  Date(): time_point_(std::chrono::system_clock::now()) {}

  Date(const int year, const int month, const int day) {
    if (month < 1 || month > 12 || day < 1 || day > 31) {
      throw std::invalid_argument("Invalid date components.");
    }
    std::tm tm = {};
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    time_point_ = std::chrono::system_clock::from_time_t(std::mktime(&tm));
  }

  Date(const int year, const int month, const int day, const int hours, const int minutes, const int seconds) {
    if (month < 1 || month > 12 || day < 1 || day > 31 || hours < 0 || hours > 23 || minutes < 0 || minutes > 59 || seconds < 0 || seconds > 59) {
      throw std::invalid_argument("Invalid date-time components.");
    }
    std::tm tm = {};
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = hours;
    tm.tm_min = minutes;
    tm.tm_sec = seconds;
    time_point_ = std::chrono::system_clock::from_time_t(std::mktime(&tm));
  }

  explicit Date(const long long timestamp) {
    time_point_ = std::chrono::system_clock::time_point(std::chrono::milliseconds(timestamp));
  }

  /// \brief Creates a copy of the current object.
  /// \returns A new Date object with the same date and time as the current object.
  [[nodiscard]] auto clone() const -> Date {
    return Date(getTime());
  }

  /// \brief Compares the current Date object with another for equality.
  /// \param other The Date object to compare with.
  /// \returns True if the current Date object has the same date and time as the other, false otherwise.
  [[nodiscard]] auto equals(const Date& other) const -> bool {
    return time_point_ == other.time_point_;
  }

  /// \brief Checks if the current Date object is after another.
  /// \param other The Date object to compare with.
  /// \returns True if the current Date object is after the other, false otherwise.
  [[nodiscard]] auto after(const Date& other) const -> bool {
    return time_point_ > other.time_point_;
  }

  /// \brief Checks if the current Date object is before another.
  /// \param other The Date object to compare with.
  /// \returns True if the current Date object is before the other, false otherwise.
  [[nodiscard]] auto before(const Date& other) const -> bool {
    return time_point_ < other.time_point_;
  }

  /// \brief Gets the time in milliseconds since the Unix epoch (January 1, 1970, 00:00:00 GMT).
  /// \returns The time in milliseconds since the Unix epoch.
  [[nodiscard]] auto getTime() const -> long long {
    return std::chrono::duration_cast<std::chrono::milliseconds>(time_point_.time_since_epoch()).count();
  }

  /// \brief Retrieves the year component of the date.
  /// \returns The year as an integer.
  [[nodiscard]] auto getYear() const -> int {
    return toTm().tm_year + 1900;
  }

  /// \brief Retrieves the month component of the date.
  /// \returns The month as an integer, where January is 1 and December is 12.
  [[nodiscard]] auto getMonth() const -> int {
    return toTm().tm_mon + 1;
  }

  /// \brief Retrieves the day component of the date.
  /// \returns The day of the month as an integer, where 1 is the first day of the month and 31 is the last.
  [[nodiscard]] auto getDay() const -> int {
    return toTm().tm_mday;
  }

  /// \brief Converts the date to a string representation.
  /// \returns A string representation of the date in the format "YYYY-MM-DD HH:MM:SS".
  [[nodiscard]] auto toString() const -> std::string {
    const auto tm = toTm();
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
  }

  /// \brief Computes the hash code for the Date object.
  /// \returns A hash code as a size_t derived from the time in milliseconds since the Unix epoch.
  [[nodiscard]] auto hashCode() const -> size_t {
    return std::hash<long long>()(getTime());
  }

private:
  std::chrono::system_clock::time_point time_point_;

  /// \brief Converts the date to a tm object.
  /// \returns A tm object representing the date.
  [[nodiscard]] auto toTm() const -> std::tm {
    const auto timeT = std::chrono::system_clock::to_time_t(time_point_);
    std::tm tm = {};
    localtime_s(&tm, &timeT);
    return tm;
  }
};
}
