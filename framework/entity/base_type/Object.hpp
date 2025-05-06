#pragma once
#include <format>
#include <iostream>

namespace framework {
  class Object {
  public:
    Object();
    virtual ~Object();
    [[nodiscard]] virtual auto clone() const -> std::unique_ptr<Object>;
    [[nodiscard]] auto getClass() const -> const std::type_info&;
    [[nodiscard]] virtual auto equals(const Object& other) const -> bool;
    [[nodiscard]] virtual auto hashCode() const -> size_t;
    [[nodiscard]] virtual auto toString() const -> std::string;

  private:
    friend std::formatter<Object>;
  };
}

template <>
struct std::formatter<framework::Object> {
  constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator {
    const auto begin = ctx.begin();
    if (const auto end = ctx.end(); begin != end && *begin != '}') {
      throw std::format_error("invalid format");
    }
    return begin;
  }

  static auto format(const framework::Object& content, format_context& ctx)
    -> back_insert_iterator<_Fmt_buffer<char>> {
    return std::format_to(ctx.out(), "Object{{hashCode:{}}}", content.hashCode());
  }
};

inline auto operator<<(std::ostream& os, const framework::Object& object) -> std::ostream& {
  return os << object.toString();
}
