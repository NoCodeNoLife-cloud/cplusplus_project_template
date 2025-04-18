#include "Character.hpp"

namespace framework::entity::base_type {

Character::Character(const char value) : value_(value) {}

Character::~Character() = default;

Character::operator char() const { return value_; }

std::string Character::toString() const { return std::format("{}", *this); }

auto Character::equals(const Character& other) const -> bool { return value_ == other.value_; }

auto Character::compareTo(const Character& other) const -> int32_t { return value_ - other.value_; }

auto Character::isLetter(const char c) -> bool { return std::isalpha(c); }

auto Character::isDigit(const char c) -> bool { return std::isdigit(c); }

auto Character::isLetterOrDigit(const char c) -> bool { return std::isalnum(c); }

auto Character::isUpperCase(const char c) -> bool { return std::isupper(c); }

auto Character::isLowerCase(const char c) -> bool { return std::islower(c); }

auto Character::toUpperCase(const char c) -> int32_t { return std::toupper(c); }

auto Character::toLowerCase(const char c) -> int32_t { return std::tolower(c); }

auto Character::characterValue() const -> char { return value_; }

auto Character::operator==(const Character& other) const -> bool { return equals(other); }

auto Character::operator!=(const Character& other) const -> bool { return !equals(other); }

auto Character::operator<(const Character& other) const -> bool { return value_ < other.value_; }

auto Character::operator>(const Character& other) const -> bool { return value_ > other.value_; }

auto Character::operator<=(const Character& other) const -> bool { return value_ <= other.value_; }

auto Character::operator>=(const Character& other) const -> bool { return value_ >= other.value_; }

}  // namespace framework::entity::base_type
