#include <entity/base_type/Object.hpp>

namespace framework {
  Object::Object() = default;
  Object::~Object() = default;

  auto Object::clone() const -> std::unique_ptr<Object> {
    return std::make_unique<Object>(Object(*this));
  }

  auto Object::getClass() const -> const std::type_info& {
    return typeid(*this);
  }

  auto Object::equals(const Object& other) const -> bool {
    if (typeid(*this) != typeid(other)) {
      return false;
    }
    return this == &other;
  }

  auto Object::hashCode() const -> size_t {
    return reinterpret_cast<size_t>(this);
  }

  auto Object::toString() const -> std::string {
    return std::format("{}", *this);
  }
}
