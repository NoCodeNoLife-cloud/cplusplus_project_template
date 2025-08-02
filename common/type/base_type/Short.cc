#include "Short.hpp"

#include <boost/functional/hash.hpp>
#include <stdexcept>

namespace common {
Short::Short(const int16_t value) : value_(value) {}

Short::~Short() = default;

Short::Short(const Short& other) : value_(other.value_) {}

Short::Short(Short&& other) noexcept : value_(other.value_) {}

Short& Short::operator=(const Short& other) {
  if (this != &other) {
    value_ = other.value_;
  }
  return *this;
}

Short& Short::operator=(Short&& other) noexcept {
  if (this != &other) {
    value_ = other.value_;
  }
  return *this;
}

size_t Short::hashCode() const {
  size_t seed = 0;
  boost::hash_combine(seed, getClass());
  boost::hash_combine(seed, value_);
  return seed;
}

Short::operator int16_t() const { return value_; }

std::string Short::toString() const { return std::format("{}", *this); }

auto Short::shortValue() const -> int16_t { return value_; }

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

auto Short::operator<=>(const Short& other) const -> std::partial_ordering { return value_ <=> other.value_; }

auto Short::operator==(const Short& other) const -> bool { return value_ == other.value_; }

auto Short::operator+(const Short& other) const -> Short { return Short(static_cast<int16_t>(this->value_ + other.value_)); }

auto Short::operator-(const Short& other) const -> Short { return Short(static_cast<int16_t>(this->value_ - other.value_)); }

auto Short::operator*(const Short& other) const -> Short { return Short(static_cast<int16_t>(this->value_ * other.value_)); }

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
}  // namespace common
