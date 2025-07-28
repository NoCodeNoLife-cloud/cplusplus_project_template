#include "Character.hpp"

#include <boost/functional/hash.hpp>
#include <cctype>

namespace common {
Character::Character(const char value) : value_(value) {}

Character::~Character() = default;

Character::Character(const Character& other) : value_(other.value_) {}

Character::Character(Character&& other) noexcept : value_(other.value_) {}

Character& Character::operator=(const Character& other) {
  if (this != &other) {
    value_ = other.value_;
  }
  return *this;
}

Character& Character::operator=(Character&& other) noexcept {
  if (this != &other) {
    value_ = other.value_;
  }
  return *this;
}

size_t Character::hashCode() const {
  size_t seed = 0;
  boost::hash_combine(seed, getClass());
  boost::hash_combine(seed, value_);
  return seed;
}

std::string Character::toString() const { return std::format("{}", *this); }

Character::operator char() const { return value_; }

auto Character::isLetter(const char c) -> bool { return std::isalpha(c); }

auto Character::isDigit(const char c) -> bool { return std::isdigit(c); }

auto Character::isLetterOrDigit(const char c) -> bool {
  return std::isalnum(c);
}

auto Character::isUpperCase(const char c) -> bool { return std::isupper(c); }

auto Character::isLowerCase(const char c) -> bool { return std::islower(c); }

auto Character::toUpperCase(const char c) -> int32_t { return std::toupper(c); }

auto Character::toLowerCase(const char c) -> int32_t { return std::tolower(c); }

auto Character::characterValue() const -> char { return value_; }

auto Character::operator<=>(const Character& other) const
    -> std::partial_ordering {
  return value_ <=> other.value_;
}

auto Character::operator==(const Character& other) const -> bool {
  return value_ == other.value_;
}
}  // namespace common
