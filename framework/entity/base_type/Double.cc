#include "Double.hpp"

namespace framework::entity::base_type {

Double::Double(const double value) : value_(value) {}

Double::~Double() = default;

Double::operator double() const { return value_; }

std::string Double::toString() const { return std::format("{}", *this); }

auto Double::equals(const Double& other) const -> bool { return value_ == other.value_; }

auto Double::compareTo(const Double& other) const -> int32_t { return (value_ > other.value_) - (value_ < other.value_); }

auto Double::doubleValue() const -> double { return value_; }

auto Double::parseDouble(const std::string& str) -> Double {
  try {
    const double result = std::stod(str);
    return Double(result);
  } catch (const std::invalid_argument&) {
    throw std::invalid_argument("Invalid input string for Double conversion");
  } catch (const std::out_of_range&) {
    throw std::out_of_range("Value out of range for Double");
  }
}

auto Double::operator==(const Double& other) const -> bool { return value_ == other.value_; }

auto Double::operator!=(const Double& other) const -> bool { return value_ != other.value_; }

auto Double::operator<(const Double& other) const -> bool { return value_ < other.value_; }

auto Double::operator>(const Double& other) const -> bool { return value_ > other.value_; }

auto Double::operator<=(const Double& other) const -> bool { return value_ <= other.value_; }

auto Double::operator>=(const Double& other) const -> bool { return value_ >= other.value_; }

auto Double::operator+(const Double& other) const -> Double { return Double(this->value_ + other.value_); }

auto Double::operator-(const Double& other) const -> Double { return Double(this->value_ - other.value_); }

auto Double::operator*(const Double& other) const -> Double { return Double(this->value_ * other.value_); }

auto Double::operator/(const Double& other) const -> Double {
  if (other.value_ == 0.0) {
    throw std::overflow_error("Division by zero");
  }
  return Double(this->value_ / other.value_);
}

}  // namespace framework::entity::base_type
