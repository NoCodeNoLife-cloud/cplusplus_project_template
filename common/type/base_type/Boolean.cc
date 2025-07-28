#include "Boolean.hpp"

#include <boost/functional/hash.hpp>
#include <stdexcept>

namespace common {
Boolean::Boolean(const bool value) : value_(value) {}

Boolean::~Boolean() = default;

Boolean::Boolean(const Boolean& other) : value_(other.value_) {}

Boolean::Boolean(Boolean&& other) noexcept : value_(other.value_) {}

Boolean& Boolean::operator=(const Boolean& other) {
  if (this != &other) {
    value_ = other.value_;
  }
  return *this;
}

Boolean& Boolean::operator=(Boolean&& other) noexcept {
  if (this != &other) {
    value_ = other.value_;
  }
  return *this;
}

size_t Boolean::hashCode() const {
  size_t seed = 0;
  boost::hash_combine(seed, getClass());
  boost::hash_combine(seed, value_);
  return seed;
}

std::string Boolean::toString() const { return std::format("{}", *this); }

Boolean::operator bool() const { return value_; }

auto Boolean::boolValue() const -> bool { return value_; }

auto Boolean::parseBoolean(const std::string& str) -> Boolean {
  if (str == "true" || str == "TRUE") {
    return Boolean(true);
  }
  if (str == "false" || str == "FALSE") {
    return Boolean(false);
  }
  throw std::invalid_argument("Invalid input string for Boolean conversion");
}

auto Boolean::booleanValue() const -> bool { return value_; }

auto Boolean::operator<=>(const Boolean& other) const -> std::partial_ordering {
  return value_ <=> other.value_;
}

auto Boolean::operator==(const Boolean& other) const -> bool {
  return value_ == other.value_;
}
}  // namespace common
