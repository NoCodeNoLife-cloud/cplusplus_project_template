#pragma once
#include <format>
#include <string>
#include <typeinfo>

#include "utils/format/GenericFormatter.hpp"

namespace common {
class Object {
 public:
  virtual ~Object() = default;
  [[nodiscard]] virtual auto getClass() const -> const std::type_info&;
  [[nodiscard]] virtual auto hashCode() const -> size_t;
  [[nodiscard]] virtual auto toString() const -> std::string;

 private:
  friend std::formatter<Object>;
};
}  // namespace common

template <>
struct std::formatter<common::Object>
    : common::GenericFormatter<common::Object> {};
