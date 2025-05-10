#pragma once
#include <format/GenericFormatter.hpp>

namespace common {
  class Object {
  public:
    Object();

    virtual ~Object();

    [[nodiscard]] auto getClass() const -> const std::type_info&;

    [[nodiscard]] virtual auto hashCode() const -> size_t;

    [[nodiscard]] virtual auto toString() const -> std::string;

  private:
    friend std::formatter<Object>;
  };
}

template <>
struct std::formatter<common::Object> : common::GenericFormatter<common::Object> {};
