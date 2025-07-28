#include "BigInteger.hpp"

#include <iostream>

namespace common {
BigInteger::BigInteger() : value_(0) {}

BigInteger::BigInteger(const std::string& str) : value_(str) {}

BigInteger::BigInteger(const int64_t num) : value_(num) {}

auto BigInteger::operator+(const BigInteger& other) const -> BigInteger {
  return BigInteger((value_ + other.value_).convert_to<std::string>());
}

auto BigInteger::operator-(const BigInteger& other) const -> BigInteger {
  return BigInteger((value_ - other.value_).convert_to<std::string>());
}

auto BigInteger::operator*(const BigInteger& other) const -> BigInteger {
  return BigInteger((value_ * other.value_).convert_to<std::string>());
}

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

auto BigInteger::operator<=>(const BigInteger& other) const
    -> std::partial_ordering {
  if (value_ < other.value_) {
    return std::strong_ordering::less;
  }
  if (value_ > other.value_) {
    return std::strong_ordering::greater;
  }
  return std::strong_ordering::equal;
}

auto BigInteger::fromString(const std::string& str) -> BigInteger {
  return BigInteger(str);
}

auto BigInteger::fromInt(const int64_t num) -> BigInteger {
  return BigInteger(num);
}
}  // namespace common
