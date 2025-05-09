#include <stdexcept>
#include <entity/base_type/Short.hpp>

namespace common {
  Short::Short(const int16_t value) : value_(value) {}

  Short::~Short() = default;

  auto Short::clone() const -> std::unique_ptr<ICloneable> {
    return std::make_unique<Short>(value_);
  }

  Short::operator short() const {
    return value_;
  }

  auto Short::shortValue() const -> int16_t {
    return value_;
  }

  auto Short::equals(const Short& other) const -> bool {
    return value_ == other.value_;
  }

  auto Short::compareTo(const Short& other) const -> int32_t {
    return value_ - other.value_;
  }

  auto Short::parseShort(const std::string& str) -> Short {
    try {
      const auto value = std::stoi(str);
      if (value > MAX_VALUE || value < MIN_VALUE) {
        throw std::out_of_range("Value out of range for Short");
      }
      return Short(static_cast<int16_t>(value));
    } catch (const std::invalid_argument&) {
      throw std::invalid_argument("Invalid input string for Short conversion");
    } catch (const std::out_of_range&) {
      throw std::out_of_range("Value out of range for Short");
    }
  }

  auto Short::operator<=>(const Short& other) const -> std::partial_ordering {
    return value_ <=> other.value_;
  }

  auto Short::operator+(const Short& other) const -> Short {
    return Short(static_cast<int16_t>(this->value_ + other.value_));
  }

  auto Short::operator-(const Short& other) const -> Short {
    return Short(static_cast<int16_t>(this->value_ - other.value_));
  }

  auto Short::operator*(const Short& other) const -> Short {
    return Short(static_cast<int16_t>(this->value_ * other.value_));
  }

  auto Short::operator/(const Short& other) const -> Short {
    if (other.value_ == 0) {
      throw std::overflow_error("Division by zero");
    }
    return Short(static_cast<int16_t>(this->value_ / other.value_));
  }

  auto Short::operator%(const Short& other) const -> Short {
    if (other.value_ == 0) {
      throw std::overflow_error("Modulo by zero");
    }
    return Short(static_cast<int16_t>(this->value_ % other.value_));
  }
}
