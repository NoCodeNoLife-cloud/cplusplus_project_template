#pragma once
#include <format>
#include <string>
#include <typeinfo>

#include "utils/format/GenericFormatter.hpp"

namespace common {
/// @brief Base class for all objects in the system.
/// @details This class provides basic functionality for type information, hashing, and string representation.
/// It is designed to be inherited by other classes that need these features.
class Object {
 public:
  virtual ~Object() = default;

  /// @brief Get the type information of the object.
  /// @return const std::type_info& The type information.
  [[nodiscard]] virtual auto getClass() const -> const std::type_info&;

  /// @brief Get the hash code of the object.
  /// @return size_t The hash code.
  [[nodiscard]] virtual auto hashCode() const -> size_t;

  /// @brief Convert the object to a string representation.
  /// @return std::string The string representation.
  [[nodiscard]] virtual auto toString() const -> std::string;

 private:
  friend std::formatter<Object>;
};
}  // namespace common

template <>
struct std::formatter<common::Object> : common::GenericFormatter<common::Object> {};
