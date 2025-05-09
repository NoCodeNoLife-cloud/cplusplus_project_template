#include <stdexcept>
#include <boost/functional/hash.hpp>
#include <entity/base_type/Long.hpp>

namespace common {
  Long::Long(const int64_t value) : value_(value) {}

  Long::~Long() = default;

  size_t Long::hashCode() const {
    size_t seed = 0;
    boost::hash_combine(seed, getClass());
    boost::hash_combine(seed, value_);
    return seed;
  }

  std::string Long::toString() const {
    return std::string(getClass().name()) + "{" + std::to_string(value_) + "}";
  }

  Long::operator int64_t() const {
    return value_;
  }

  auto Long::longValue() const -> int64_t {
    return value_;
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

  auto Long::operator<=>(const Long& other) const -> std::partial_ordering {
    return value_ <=> other.value_;
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
