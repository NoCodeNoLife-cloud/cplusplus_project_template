#include <stdexcept>
#include <entity/base_type/Boolean.hpp>

namespace common {
  Boolean::Boolean(const bool value) : value_(value) {}

  Boolean::~Boolean() = default;

  auto Boolean::clone() const -> std::unique_ptr<ICloneable> {
    return std::make_unique<Boolean>(value_);
  }

  Boolean::operator bool() const {
    return value_;
  }

  auto Boolean::boolValue() const -> bool {
    return value_;
  }

  auto Boolean::compareTo(const Boolean& other) const -> int32_t {
    return value_ - other.value_;
  }

  auto Boolean::parseBoolean(const std::string& str) -> Boolean {
    if (str == "true" || str == "TRUE") {
      return Boolean(true);
    }
    if (str == "false" || str == "FALSE") {
      return Boolean(false);
    }
    throw std::invalid_argument("Invalid input string for Boolean conversion");
  }

  auto Boolean::booleanValue() const -> bool {
    return value_;
  }

  auto Boolean::equals(const Boolean& other) const -> bool {
    return value_ == other.value_;
  }

  auto Boolean::operator<=>(const Boolean& other) const -> std::partial_ordering {
    return value_ <=> other.value_;
  }
}
