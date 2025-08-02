#pragma once
#include <format>
#include <sstream>

namespace common {
template <typename T, auto... Members>
struct GenericFormatter {
  constexpr static auto parse(std::format_parse_context& ctx) -> std::format_parse_context::const_iterator { return ctx.begin(); }

  static auto format(const T& content, std::format_context& ctx) -> std::back_insert_iterator<std::_Fmt_buffer<char>> {
    std::ostringstream oss;

    oss << typeid(T).name() << "{";
    bool first = true;
    // ReSharper disable once CppDFAConstantConditions
    ((oss << (first ? "" : ", ") << std::invoke(Members, content), first = false), ...);
    oss << "}";

    return std::format_to(ctx.out(), "{}", oss.str());
  }
};
}  // namespace common
