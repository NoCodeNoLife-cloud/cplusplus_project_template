#include "SimpleDateFormatter.hpp"

#include <iomanip>
#include <sstream>

namespace common {
SimpleDateFormatter::SimpleDateFormatter(const std::string& pattern) {
  validatePattern(pattern);
  this->pattern_ = pattern;
}

auto SimpleDateFormatter::applyPattern(const std::string& newPattern) -> void {
  validatePattern(newPattern);
  this->pattern_ = newPattern;
}

auto SimpleDateFormatter::toPattern() const -> std::string {
  return this->pattern_;
}

auto SimpleDateFormatter::format(const std::tm& date) const -> std::string {
  std::ostringstream oss;
  try {
    oss << std::put_time(&date, pattern_.c_str());
  } catch (const std::exception& e) {
    throw std::runtime_error("Error formatting date: " + std::string(e.what()));
  }
  return oss.str();
}

auto SimpleDateFormatter::parse(const std::string& dateStr) const -> std::tm {
  std::istringstream iss(dateStr);
  std::tm date = {};
  try {
    iss >> std::get_time(&date, pattern_.c_str());
    if (iss.fail()) {
      throw std::runtime_error("Failed to parse date: " + dateStr);
    }
  } catch (const std::exception& e) {
    throw std::runtime_error("Error parsing date: " + std::string(e.what()));
  }
  return date;
}

auto SimpleDateFormatter::equals(const SimpleDateFormatter& other) const
    -> bool {
  return this->pattern_ == other.pattern_;
}

auto SimpleDateFormatter::hashCode() const -> size_t {
  return std::hash<std::string>{}(this->pattern_);
}

auto SimpleDateFormatter::validatePattern(const std::string& pat) -> void {
  if (pat.empty()) {
    throw std::invalid_argument("Pattern cannot be empty.");
  }
}
}  // namespace common
