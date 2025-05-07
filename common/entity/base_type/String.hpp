#pragma once
#include <format>
#include <iostream>
#include <regex>
#include <string>
#include <entity/base_type/Object.hpp>
#include <entity/interface/IComparable.hpp>

namespace common {
  class String final : public Object, IComparable<String> {
  public:
    String();
    explicit String(const char* str);
    explicit String(std::string str);
    [[nodiscard]] auto charAt(int32_t index) const -> char;
    [[nodiscard]] auto length() const -> size_t;
    [[nodiscard]] auto substring(int32_t beginIndex, int32_t endIndex) const -> String;
    [[nodiscard]] auto concat(const String& str) const -> String;
    [[nodiscard]] auto compareTo(const String& anotherString) const -> int32_t override;
    [[nodiscard]] auto compareToIgnoreCase(const String& anotherString) const -> int32_t;
    [[nodiscard]] auto isEmpty() const -> bool;
    [[nodiscard]] auto contains(const String& str) const -> bool;
    [[nodiscard]] auto replace(char oldChar, char newChar) const -> String;
    [[nodiscard]] auto toLowerCase() const -> String;
    [[nodiscard]] auto toUpperCase() const -> String;
    [[nodiscard]] auto trim() const -> String;
    [[nodiscard]] auto toStdString() const -> std::string;
    [[nodiscard]] auto equals(const String& other) const -> bool override;
    [[nodiscard]] auto codePointAt(int32_t index) const -> int32_t;
    [[nodiscard]] auto codePointBefore(int32_t index) const -> int32_t;
    [[nodiscard]] auto codePointCount(int32_t beginIndex, int32_t endIndex) const -> int32_t;
    [[nodiscard]] auto indexOf(char ch) const -> int32_t;
    [[nodiscard]] auto indexOf(char ch, int32_t fromIndex) const -> int32_t;
    [[nodiscard]] auto indexOf(const String& str) const -> int32_t;
    [[nodiscard]] auto indexOf(const String& str, int32_t fromIndex) const -> int32_t;
    [[nodiscard]] auto lastIndexOf(char ch) const -> int32_t;
    [[nodiscard]] auto lastIndexOf(char ch, int32_t fromIndex) const -> int32_t;
    [[nodiscard]] auto lastIndexOf(const String& str) const -> int32_t;
    [[nodiscard]] auto lastIndexOf(const String& str, int32_t fromIndex) const -> int32_t;
    [[nodiscard]] auto matches(const std::string& regex) const -> bool;
    [[nodiscard]] auto replaceAll(const std::string& regex, const std::string& replacement) const -> String;
    [[nodiscard]] auto replaceFirst(const std::string& regex, const std::string& replacement) const -> String;
    [[nodiscard]] auto split(const std::string& regex) const -> std::vector<String>;
    [[nodiscard]] auto split(const std::string& regex, int32_t limit) const -> std::vector<String>;
    static auto valueOf(bool b) -> String;
    static auto valueOf(char c) -> String;
    static auto valueOf(const char* data) -> String;
    static auto valueOf(int32_t i) -> String;
    static auto valueOf(int64_t l) -> String;
    static auto valueOf(float f) -> String;
    static auto valueOf(double d) -> String;
    static auto valueOf(const String& str) -> String;
    [[nodiscard]] auto regionMatches(int32_t tOffset, const String& other, int32_t oOffset, int32_t len) const -> bool;
    [[nodiscard]] auto regionMatches(bool ignoreCase, int32_t tOffset, const String& other, int32_t oOffset, int32_t len) const -> bool;
    auto operator<=>(const String& other) const -> std::partial_ordering;
    auto operator+(const String& str) const -> String;
    [[nodiscard]] auto toString() const -> std::string override;

  private:
    std::string data_{};
    friend std::formatter<String>;
  };
}

template <>
struct std::formatter<common::String> {
  constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator {
    const auto begin = ctx.begin();
    if (const auto end = ctx.end(); begin != end && *begin != '}') {
      throw std::format_error("invalid format");
    }
    return begin;
  }

  static auto format(const common::String& content, format_context& ctx)
    -> back_insert_iterator<_Fmt_buffer<char>> {
    return std::format_to(ctx.out(), "String{{data: {}}}", content.data_);
  }
};

inline auto operator<<(std::ostream& os, const common::String& content) -> std::ostream& {
  return os << std::format("{}", content);
}
