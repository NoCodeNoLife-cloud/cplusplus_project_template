#pragma once
#include <format>
#include <iostream>

namespace framework::entity::base_type {

class Object {
 public:
  Object();

  virtual ~Object();

  [[nodiscard]] auto clone() const -> std::unique_ptr<Object>;

  [[nodiscard]] auto getClass() const -> const std::type_info&;

  [[nodiscard]] auto equals(const Object& other) const -> bool;

  [[nodiscard]] auto hashCode() const -> size_t;

  [[nodiscard]] virtual auto toString() const -> std::string;

 private:
  friend std::formatter<Object>;
};

inline Object::Object() = default;

inline Object::~Object() = default;

inline auto Object::clone() const -> std::unique_ptr<Object> { return std::make_unique<Object>(Object(*this)); }

inline auto Object::getClass() const -> const std::type_info& { return typeid(*this); }

inline auto Object::equals(const Object& other) const -> bool {
  if (typeid(*this) != typeid(other)) {
    return false;
  }
  return this == &other;
}

inline auto Object::hashCode() const -> size_t { return std::hash<const void*>{}(this); }

inline auto Object::toString() const -> std::string { return std::format("{}", *this); }

}  // namespace framework::entity::base_type

template <>
struct std::formatter<framework::entity::base_type::Object> {
  constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator {
    const auto begin = ctx.begin();
    if (const auto end = ctx.end(); begin != end && *begin != '}') {
      throw std::format_error("invalid format");
    }
    return begin;
  }

  static auto format(const framework::entity::base_type::Object& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>> { return std::format_to(ctx.out(), "Object{{hashCode:{}}}", content.hashCode()); }
};

inline auto operator<<(std::ostream& os, const framework::entity::base_type::Object& object) -> std::ostream& { return os << std::format("{}", object); }
