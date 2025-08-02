#include "Double.hpp"

#include <boost/functional/hash.hpp>
#include <stdexcept>

namespace common {
Double::Double(const double value) : value_(value) {}

Double::~Double() = default;

Double::Double(const Double& other) : value_(other.value_) {}

Double::Double(Double&& other) noexcept : value_(other.value_) {}

Double& Double::operator=(const Double& other) {
  if (this != &other) {
    value_ = other.value_;
  }
  return *this;
}

Double& Double::operator=(Double&& other) noexcept {
  if (this != &other) {
    value_ = other.value_;
  }
  return *this;
}

size_t Double::hashCode() const {
  size_t seed = 0;
  boost::hash_combine(seed, getClass());
  boost::hash_combine(seed, value_);
  return seed;
}

std::string Double::toString() const { return std::format("{}", *this); }

Double::operator double() const { return value_; }

auto Double::doubleValue() const -> double { return value_; }

auto Double::parseDouble(const std::string& str) -> Double {
  try {
    size_t idx = 0;
    const double result = std::stod(str, &idx);
    if (idx != str.size()) {
      throw std::invalid_argument("Invalid input string for Double conversion");
    }
    return Double(result);
  } catch (const std::invalid_argument&) {
    throw std::invalid_argument("Invalid input string for Double conversion");
  } catch (const std::out_of_range&) {
    throw std::out_of_range("Value out of range for Double");
  }
}

auto Double::operator<=>(const Double& other) const -> std::partial_ordering { return value_ <=> other.value_; }

auto Double::operator==(const Double& other) const -> bool { return value_ == other.value_; }

auto Double::operator+(const Double& other) const -> Double { return Double(this->value_ + other.value_); }

auto Double::operator-(const Double& other) const -> Double { return Double(this->value_ - other.value_); }

auto Double::operator*(const Double& other) const -> Double { return Double(this->value_ * other.value_); }

auto Double::operator/(const Double& other) const -> Double {
  if (other.value_ == 0.0) {
    throw std::overflow_error("Division by zero");
  }
  return Double(this->value_ / other.value_);
}
}  // namespace common
