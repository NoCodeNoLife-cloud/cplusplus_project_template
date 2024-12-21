#include "BigInteger.hpp"

#include <iostream>

namespace framework::entity::base_type {

BigInteger::BigInteger() : value_(0) {}

BigInteger::BigInteger(const std::string& str) : value_(str) {}

BigInteger::BigInteger(const int64_t num) : value_(num) {}

auto BigInteger::operator+(const BigInteger& other) const -> BigInteger { return BigInteger((value_ + other.value_).convert_to<std::string>()); }

auto BigInteger::operator-(const BigInteger& other) const -> BigInteger { return BigInteger((value_ - other.value_).convert_to<std::string>()); }

auto BigInteger::operator*(const BigInteger& other) const -> BigInteger { return BigInteger((value_ * other.value_).convert_to<std::string>()); }

auto BigInteger::operator/(const BigInteger& other) const -> BigInteger {
  if (other.value_ == 0) {
    throw std::invalid_argument("Division by zero");
  }
  return BigInteger((value_ / other.value_).convert_to<std::string>());
}

auto BigInteger::operator%(const BigInteger& other) const -> BigInteger {
  if (other.value_ == 0) {
    throw std::invalid_argument("Modulo by zero");
  }
  return BigInteger((value_ % other.value_).convert_to<std::string>());
}

auto BigInteger::operator==(const BigInteger& other) const -> bool { return value_ == other.value_; }

auto BigInteger::operator!=(const BigInteger& other) const -> bool { return value_ != other.value_; }

auto BigInteger::operator<(const BigInteger& other) const -> bool { return value_ < other.value_; }

auto BigInteger::operator<=(const BigInteger& other) const -> bool { return value_ <= other.value_; }

auto BigInteger::operator>(const BigInteger& other) const -> bool { return value_ > other.value_; }

auto BigInteger::operator>=(const BigInteger& other) const -> bool { return value_ >= other.value_; }

auto BigInteger::toString() const -> std::string { return value_.str(); }

auto BigInteger::fromString(const std::string& str) -> BigInteger { return BigInteger(str); }

auto BigInteger::fromInt(const int64_t num) -> BigInteger { return BigInteger(num); }

}  // namespace framework::entity::base_type
