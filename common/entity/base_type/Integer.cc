#include <entity/base_type/Integer.hpp>

namespace common {
  Integer::Integer(const int32_t value) : value_(value) {}

  Integer::~Integer() = default;

  auto Integer::clone() const -> std::unique_ptr<ICloneable> {
    return std::make_unique<Integer>(value_);
  }

  Integer::operator int32_t() const {
    return value_;
  }

  auto Integer::toString() const -> std::string {
    return std::format("{}", *this);
  }

  auto Integer::intValue() const -> int32_t {
    return value_;
  }

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

  auto Integer::compareTo(const Integer& other) const -> int32_t {
    return value_ - other.value_;
  }

  bool Integer::equals(const Integer& other) const {
    return value_ == other.value_;
  }

  auto Integer::operator<=>(const Integer& other) const -> std::partial_ordering {
    return value_ <=> other.value_;
  }

  auto Integer::operator+(const Integer& other) const -> Integer {
    return Integer(this->value_ + other.value_);
  }

  auto Integer::operator-(const Integer& other) const -> Integer {
    return Integer(this->value_ - other.value_);
  }

  auto Integer::operator*(const Integer& other) const -> Integer {
    return Integer(this->value_ * other.value_);
  }

  auto Integer::operator/(const Integer& other) const -> Integer {
    if (other.value_ == 0) {
      throw std::invalid_argument("Division by zero is not allowed.");
    }
    return Integer(this->value_ / other.value_);
  }
}
