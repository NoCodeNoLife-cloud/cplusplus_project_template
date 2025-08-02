#include "Float.hpp"

#include <boost/functional/hash.hpp>
#include <stdexcept>

namespace common {
Float::Float(const float value) : value_(value) {}

Float::~Float() = default;

Float::Float(const Float& other) : value_(other.value_) {}

Float::Float(Float&& other) noexcept : value_(other.value_) {}

Float& Float::operator=(const Float& other) {
  if (this != &other) {
    value_ = other.value_;
  }
  return *this;
}

Float& Float::operator=(Float&& other) noexcept {
  if (this != &other) {
    value_ = other.value_;
  }
  return *this;
}

size_t Float::hashCode() const {
  size_t seed = 0;
  boost::hash_combine(seed, getClass());
  boost::hash_combine(seed, value_);
  return seed;
}

std::string Float::toString() const { return std::format("{}", *this); }

Float::operator float() const { return value_; }

auto Float::floatValue() const -> float { return value_; }

auto Float::parseFloat(const std::string& str) -> Float {
  try {
    const float result = std::stof(str);
    return Float(result);
  } catch (const std::invalid_argument&) {
    throw std::invalid_argument("Invalid input string for Float conversion");
  } catch (const std::out_of_range&) {
    throw std::out_of_range("Value out of range for Float");
  }
}

auto Float::operator<=>(const Float& other) const -> std::partial_ordering { return value_ <=> other.value_; }

auto Float::operator==(const Float& other) const -> bool { return value_ == other.value_; }

auto Float::operator+(const Float& other) const -> Float { return Float(this->value_ + other.value_); }

auto Float::operator-(const Float& other) const -> Float { return Float(this->value_ - other.value_); }

auto Float::operator*(const Float& other) const -> Float { return Float(this->value_ * other.value_); }

auto Float::operator/(const Float& other) const -> Float {
  if (other.value_ == 0.0f) {
    throw std::overflow_error("Division by zero");
  }
  return Float(this->value_ / other.value_);
}
}  // namespace common
