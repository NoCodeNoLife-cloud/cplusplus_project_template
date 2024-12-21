#pragma once
#include <format>
#include <iostream>

namespace common::entity::base_type {
/// \class Object
/// \brief The base class for all objects.
class Object {
public:
  Object() = default;

  virtual ~Object() = default;

  /// \brief Clone the object
  /// \return A clone of the object
  [[nodiscard]] auto clone() const -> std::unique_ptr<Object> {
    return std::make_unique<Object>(Object(*this));
  }

  /// \brief Get the class type of the object
  /// \return The class type
  [[nodiscard]] auto getClass() const -> const std::type_info& {
    return typeid(*this);
  }

  /// \brief Check if the object is equal to another object
  /// \param other The other object
  /// \return True if the objects are equal
  [[nodiscard]] auto equals(const Object& other) const -> bool {
    if (typeid(*this) != typeid(other)) {
      return false;
    }
    return this == &other;
  }

  /// \brief Get the hash code of the object
  /// \return The hash code
  [[nodiscard]] auto hashCode() const -> size_t {
    return std::hash<const void*>{}(this);
  }

  /// \brief Get the string representation of the object
  /// \return The string representation
  [[nodiscard]] virtual auto toString() const -> std::string {
    return std::format("{}", *this);
  }

private:
  friend std::formatter<Object>;
};
}

template <>
struct std::formatter<common::entity::base_type::Object> {
  /// \brief Custom formatter for Object class.
  /// \details This formatter is responsible for converting an Object instance
  /// into a string representation using the standard formatting utilities.
  constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator {
    const auto begin = ctx.begin();
    if (const auto end = ctx.end(); begin != end && *begin != '}') {
      throw std::format_error("invalid format");
    }
    return begin;
  }

  /// \brief Custom formatter for Object class.
  /// \details This formatter is responsible for converting an Object instance
  /// into a string representation using the standard formatting utilities.
  /// \param content The Object instance to format.
  /// \param ctx The format context to use for formatting.
  /// \return An iterator to the end of the inserted sequence.
  static auto format(const common::entity::base_type::Object& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>> {
    return std::format_to(ctx.out(), "Object{{}}", "");
  }
};

inline auto operator<<(std::ostream& os, const common::entity::base_type::Object& object) -> std::ostream& {
  return os << std::format("{}", object);
}
