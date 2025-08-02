#include "Date.hpp"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace common {
Date::Date() : time_point_(std::chrono::system_clock::now()) {}

Date::Date(const int32_t year, const int32_t month, const int32_t day) {
  if (month < 1 || month > 12 || day < 1 || day > 31) {
    throw std::invalid_argument("Invalid date components.");
  }
  std::tm tm = {};
  tm.tm_year = year - 1900;
  tm.tm_mon = month - 1;
  tm.tm_mday = day;
  time_point_ = std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

Date::Date(const int32_t year, const int32_t month, const int32_t day, const int32_t hours, const int32_t minutes, const int32_t seconds) {
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

Date::Date(const int64_t timestamp) { time_point_ = std::chrono::system_clock::time_point(std::chrono::milliseconds(timestamp)); }

auto Date::clone() const -> Date { return Date(getTime()); }

auto Date::equals(const Date& other) const -> bool { return time_point_ == other.time_point_; }

auto Date::after(const Date& other) const -> bool { return time_point_ > other.time_point_; }

auto Date::before(const Date& other) const -> bool { return time_point_ < other.time_point_; }

auto Date::getTime() const -> int64_t { return std::chrono::duration_cast<std::chrono::milliseconds>(time_point_.time_since_epoch()).count(); }

auto Date::getYear() const -> int32_t { return toTm().tm_year + 1900; }

auto Date::getMonth() const -> int32_t { return toTm().tm_mon + 1; }

auto Date::getDay() const -> int32_t { return toTm().tm_mday; }

auto Date::toString() const -> std::string {
  const auto tm = toTm();
  std::ostringstream oss;
  oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
  return oss.str();
}

auto Date::hashCode() const -> size_t { return std::hash<int64_t>()(getTime()); }

auto Date::toTm() const -> std::tm {
  const auto timeT = std::chrono::system_clock::to_time_t(time_point_);
  std::tm tm = {};
  localtime_s(&tm, &timeT);
  return tm;
}
}  // namespace common
