#include <entity/base_type/Long.hpp>

namespace framework::entity::base_type {
  Long::Long(const int64_t value) : value_(value) {}

  Long::~Long() = default;

  Long::operator int64_t() const {
    return value_;
  }

  std::string Long::toString() const {
    return std::format("{}", *this);
  }

  auto Long::longValue() const -> int64_t {
    return value_;
  }

  auto Long::equals(const Long& other) const -> bool {
    return value_ == other.value_;
  }

  auto Long::compareTo(const Long& other) const -> int32_t {
    return (value_ > other.value_) - (value_ < other.value_);
  }

  auto Long::parseLong(const std::string& str) -> Long {
    try {
      const int64_t result = std::stoll(str, nullptr, 0);
      return Long(result);
    } catch (const std::invalid_argument&) {
      throw std::invalid_argument("Invalid input string for Long conversion");
    } catch (const std::out_of_range&) {
      throw std::out_of_range("Value out of range for Long");
    }
  }

  auto Long::operator==(const Long& other) const -> bool {
    return equals(other);
  }

  auto Long::operator!=(const Long& other) const -> bool {
    return !equals(other);
  }

  auto Long::operator<(const Long& other) const -> bool {
    return value_ < other.value_;
  }

  auto Long::operator>(const Long& other) const -> bool {
    return value_ > other.value_;
  }

  auto Long::operator<=(const Long& other) const -> bool {
    return value_ <= other.value_;
  }

  auto Long::operator>=(const Long& other) const -> bool {
    return value_ >= other.value_;
  }

  auto Long::operator+(const Long& other) const -> Long {
    return Long(this->value_ + other.value_);
  }

  auto Long::operator-(const Long& other) const -> Long {
    return Long(this->value_ - other.value_);
  }

  auto Long::operator*(const Long& other) const -> Long {
    return Long(this->value_ * other.value_);
  }

  auto Long::operator/(const Long& other) const -> Long {
    if (other.value_ == 0) {
      throw std::overflow_error("Division by zero");
    }
    return Long(this->value_ / other.value_);
  }

  auto Long::operator%(const Long& other) const -> Long {
    if (other.value_ == 0) {
      throw std::overflow_error("Modulo by zero");
    }
    return Long(this->value_ % other.value_);
  }
}
