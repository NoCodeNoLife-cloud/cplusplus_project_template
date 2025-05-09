#include <boost/functional/hash.hpp>
#include <entity/base_type/Object.hpp>

namespace common {
  Object::Object() = default;
  Object::~Object() = default;
  Object::Object(const Object& other) = default;
  Object::Object(const Object&& other) noexcept {}
  Object& Object::operator=(const Object& other) = default;

  Object& Object::operator=(Object&& other) noexcept {
    return *this;
  }

  auto Object::getClass() const -> const std::type_info& {
    return typeid(*this);
  }

  auto Object::hashCode() const -> size_t {
    size_t seed = 0;
    boost::hash_combine(seed, getClass());
    boost::hash_combine(seed, reinterpret_cast<size_t>(this));
    return seed;
  }

  auto Object::toString() const -> std::string {
    return std::format("{}", *this);
  }
}
