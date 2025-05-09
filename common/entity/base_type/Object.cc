#include <string>
#include <entity/base_type/Object.hpp>

namespace common {
  Object::Object() = default;
  Object::~Object() = default;

  auto Object::getClass() const -> const std::type_info& {
    return typeid(*this);
  }

  auto Object::hashCode() const -> size_t {
    return reinterpret_cast<size_t>(this);
  }

  auto Object::toString() const -> std::string {
    return std::string(getClass().name()) + "{}";
  }
}
