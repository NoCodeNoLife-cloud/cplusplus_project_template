#include "BigDecimal.hpp"

#include <stdexcept>

namespace framework::entity::base_type {

BigDecimal::BigDecimal(const std::string& str) : value_(str) {}

BigDecimal::BigDecimal(const double num) : value_(num) {}

auto BigDecimal::operator+(const BigDecimal& other) const -> BigDecimal { return {BigDecimal((value_ + other.value_).convert_to<std::string>())}; }

auto BigDecimal::operator-(const BigDecimal& other) const -> BigDecimal { return {BigDecimal((value_ - other.value_).convert_to<std::string>())}; }

auto BigDecimal::operator*(const BigDecimal& other) const -> BigDecimal { return {BigDecimal((value_ * other.value_).convert_to<std::string>())}; }

auto BigDecimal::operator/(const BigDecimal& other) const -> BigDecimal {
  if (other.value_ == 0) {
    throw std::invalid_argument("Division by zero is not allowed.");
  }
  return {BigDecimal((value_ / other.value_).convert_to<std::string>())};
}

auto BigDecimal::operator==(const BigDecimal& other) const -> bool { return value_ == other.value_; }

auto BigDecimal::operator!=(const BigDecimal& other) const -> bool { return value_ != other.value_; }

auto BigDecimal::operator<(const BigDecimal& other) const -> bool { return value_ < other.value_; }

auto BigDecimal::operator>(const BigDecimal& other) const -> bool { return value_ > other.value_; }

auto BigDecimal::toString() const -> std::string { return value_.convert_to<std::string>(); }

}  // namespace framework::entity::base_type
