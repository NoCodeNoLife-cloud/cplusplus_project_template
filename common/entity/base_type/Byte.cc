#include <stdexcept>
#include <entity/base_type/Byte.hpp>

namespace common {
  Byte::Byte(const uint8_t value) : value_(value) {}

  Byte::~Byte() = default;

  auto Byte::clone() const -> std::unique_ptr<ICloneable> {
    return std::make_unique<Byte>(value_);
  }

  Byte::operator unsigned char() const {
    return value_;
  }

  auto Byte::equals(const Byte& other) const -> bool {
    return value_ == other.value_;
  }

  auto Byte::compareTo(const Byte& other) const -> int32_t {
    return (value_ > other.value_) - (value_ < other.value_);
  }

  auto Byte::parseByte(const std::string& str) -> Byte {
    if (str.empty()) {
      throw std::invalid_argument("Empty string cannot be parsed as byte.");
    }

    size_t pos;
    const int64_t value = std::stoll(str, &pos);
    if (pos != str.size()) {
      throw std::invalid_argument("Invalid character in byte string.");
    }
    if (value < 0 || value > 255) {
      throw std::out_of_range("Value out of range for byte.");
    }
    return Byte(static_cast<uint8_t>(value));
  }

  auto Byte::byteValue() const -> uint8_t {
    return value_;
  }

  auto Byte::operator<=>(const Byte& other) const -> std::partial_ordering {
    return value_ <=> other.value_;
  }

  auto Byte::operator+(const Byte& other) const -> Byte {
    const int64_t result = static_cast<int64_t>(value_) + static_cast<int64_t>(other.value_);
    if (result > 255) {
      throw std::overflow_error("Byte overflow in addition");
    }
    return Byte(static_cast<uint8_t>(result));
  }

  auto Byte::operator-(const Byte& other) const -> Byte {
    const int64_t result = static_cast<int64_t>(value_) - static_cast<int64_t>(other.value_);
    if (result < 0) {
      throw std::underflow_error("Byte underflow in subtraction");
    }
    return Byte(static_cast<uint8_t>(result));
  }
}
