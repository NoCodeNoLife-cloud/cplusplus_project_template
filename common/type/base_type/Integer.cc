#include "Integer.hpp"

#include <boost/functional/hash.hpp>
#include <stdexcept>

namespace common {
Integer::Integer(const int32_t value) : value_(value) {}

Integer::~Integer() = default;

Integer::Integer(const Integer& other) : value_(other.value_) {}

Integer::Integer(Integer&& other) noexcept : value_(other.value_) {}

Integer& Integer::operator=(const Integer& other) {
  if (this != &other) {
    value_ = other.value_;
  }
  return *this;
}

Integer& Integer::operator=(Integer&& other) noexcept {
  if (this != &other) {
    value_ = other.value_;
  }
  return *this;
}

size_t Integer::hashCode() const {
  size_t seed = 0;
  boost::hash_combine(seed, getClass());
  boost::hash_combine(seed, value_);
  return seed;
}

std::string Integer::toString() const { return std::format("{}", *this); }

Integer::operator int32_t() const { return value_; }

auto Integer::intValue() const -> int32_t { return value_; }

auto Integer::parseInt(const std::string& str) -> Integer {
  try {
    size_t idx;
    const int32_t result = std::stoi(str, &idx);
    if (idx != str.size()) {
      throw std::invalid_argument("Invalid input string");
    }
    return Integer(result);
  } catch (const std::out_of_range&) {
    throw std::out_of_range("Value out of range");
  }
}

auto Integer::operator<=>(const Integer& other) const -> std::partial_ordering { return value_ <=> other.value_; }

auto Integer::operator==(const Integer& other) const -> bool { return value_ == other.value_; }

auto Integer::operator+(const Integer& other) const -> Integer { return Integer(this->value_ + other.value_); }

auto Integer::operator-(const Integer& other) const -> Integer { return Integer(this->value_ - other.value_); }

auto Integer::operator*(const Integer& other) const -> Integer { return Integer(this->value_ * other.value_); }

auto Integer::operator/(const Integer& other) const -> Integer {
  if (other.value_ == 0) {
    throw std::invalid_argument("Division by zero is not allowed.");
  }
  return Integer(this->value_ / other.value_);
}
}  // namespace common
