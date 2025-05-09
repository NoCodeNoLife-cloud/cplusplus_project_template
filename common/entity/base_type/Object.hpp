#pragma once
#include <string>
#include <typeinfo>

namespace common {
  class Object {
  public:
    Object();

    virtual ~Object();

    [[nodiscard]] auto getClass() const -> const std::type_info&;

    [[nodiscard]] virtual auto hashCode() const -> size_t;

    [[nodiscard]] virtual auto toString() const -> std::string;
  };
}
