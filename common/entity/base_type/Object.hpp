#pragma once
#include <string>
#include <entity/interface/ICloneable.hpp>

namespace common {
  class Object : public ICloneable {
  public:
    Object();
    ~Object() override;
    [[nodiscard]] auto clone() const -> std::unique_ptr<ICloneable> override;
    [[nodiscard]] auto getClass() const -> const std::type_info&;
    [[nodiscard]] virtual auto equals(const Object& other) const -> bool;
    [[nodiscard]] virtual auto hashCode() const -> size_t;
  };
}
