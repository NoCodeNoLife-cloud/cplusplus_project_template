#include "Object.hpp"

#include <boost/functional/hash.hpp>

namespace common {
Object::Object() = default;
Object::~Object() = default;
Object::Object(const Object& other) = default;

Object::Object([[maybe_unused]] const Object&& other) noexcept {};
Object& Object::operator=(const Object& other) = default;

Object& Object::operator=(Object&&) noexcept { return *this; }

auto Object::getClass() const -> const std::type_info& { return typeid(*this); }

auto Object::hashCode() const -> size_t {
  constexpr size_t seed = 0;
  return seed;
}

auto Object::toString() const -> std::string {
  return std::format("{}", *this);
}
}  // namespace common
