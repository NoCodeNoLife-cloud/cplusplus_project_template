#include <entity/base_type/Float.hpp>

namespace common {
  Float::Float(const float value) : value_(value) {}

  Float::~Float() = default;

  Float::operator float() const {
    return value_;
  }

  std::string Float::toString() const {
    return std::format("{}", *this);
  }

  auto Float::equals(const Float& other) const -> bool {
    return value_ == other.value_;
  }

  auto Float::compareTo(const Float& other) const -> int32_t {
    return (value_ > other.value_) - (value_ < other.value_);
  }

  auto Float::floatValue() const -> float {
    return value_;
  }

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

  auto Float::operator==(const Float& other) const -> bool {
    return value_ == other.value_;
  }

  auto Float::operator!=(const Float& other) const -> bool {
    return value_ != other.value_;
  }

  auto Float::operator<(const Float& other) const -> bool {
    return value_ < other.value_;
  }

  auto Float::operator>(const Float& other) const -> bool {
    return value_ > other.value_;
  }

  auto Float::operator<=(const Float& other) const -> bool {
    return value_ <= other.value_;
  }

  auto Float::operator>=(const Float& other) const -> bool {
    return value_ >= other.value_;
  }

  auto Float::operator+(const Float& other) const -> Float {
    return Float(this->value_ + other.value_);
  }

  auto Float::operator-(const Float& other) const -> Float {
    return Float(this->value_ - other.value_);
  }

  auto Float::operator*(const Float& other) const -> Float {
    return Float(this->value_ * other.value_);
  }

  auto Float::operator/(const Float& other) const -> Float {
    if (other.value_ == 0.0f) {
      throw std::overflow_error("Division by zero");
    }
    return Float(this->value_ / other.value_);
  }
}
