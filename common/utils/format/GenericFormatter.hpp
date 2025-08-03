#pragma once
#include <format>
#include <sstream>

namespace common {
template <typename T, auto... Members>
struct GenericFormatter {
  /// @brief Parses the format string for the generic formatter.
  /// @param ctx The format parse context.
  /// @return An iterator to the end of the parsed range.
  constexpr static auto parse(std::format_parse_context& ctx) -> std::format_parse_context::const_iterator;

  /// @brief Formats the given content according to the parsed format.
  /// @param content The content to be formatted.
  /// @param ctx The format context.
  /// @return An iterator to the end of the formatted output.
  static auto format(const T& content, std::format_context& ctx) -> std::back_insert_iterator<std::_Fmt_buffer<char>>;
};
template <typename T, auto... Members>
constexpr auto GenericFormatter<T, Members...>::parse(std::format_parse_context& ctx) -> std::format_parse_context::const_iterator {
  return ctx.begin();
}
template <typename T, auto... Members>
auto GenericFormatter<T, Members...>::format(const T& content, std::format_context& ctx) -> std::back_insert_iterator<std::_Fmt_buffer<char>> {
  std::ostringstream oss;

  oss << typeid(T).name() << "{";
  bool first = true;
  // ReSharper disable once CppDFAConstantConditions
  ((oss << (first ? "" : ", ") << std::invoke(Members, content), first = false), ...);
  oss << "}";

  return std::format_to(ctx.out(), "{}", oss.str());
}
}  // namespace common
