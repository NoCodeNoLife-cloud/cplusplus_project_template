#include "Object.hpp"

namespace common {
auto Object::getClass() const -> const std::type_info& { return typeid(*this); }

auto Object::hashCode() const -> size_t {
  constexpr size_t seed = 0;
  return seed;
}

auto Object::toString() const -> std::string { return std::format("{}", *this); }
}  // namespace common
