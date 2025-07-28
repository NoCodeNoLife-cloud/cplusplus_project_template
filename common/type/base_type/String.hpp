#pragma once
#include "Object.hpp"

namespace common {
class String final : public Object {
 public:
  String();
  ~String() override;
  explicit String(const char* str);
  explicit String(std::string str);
  String(const String& other);
  String(String&& other) noexcept;
  String& operator=(const String& other);
  String& operator=(String&& other) noexcept;
  explicit operator std::string() const;
  [[nodiscard]] auto hashCode() const -> size_t override;
  [[nodiscard]] auto toString() const -> std::string override;
  [[nodiscard]] auto charAt(int32_t index) const -> char;
  [[nodiscard]] auto length() const -> size_t;
  [[nodiscard]] auto substring(int32_t beginIndex, int32_t endIndex) const
      -> String;
  [[nodiscard]] auto concat(const String& str) const -> String;
  [[nodiscard]] auto compareToIgnoreCase(const String& anotherString) const
      -> int32_t;
  [[nodiscard]] auto isEmpty() const -> bool;
  [[nodiscard]] auto contains(const String& str) const -> bool;
  [[nodiscard]] auto replace(char oldChar, char newChar) const -> String;
  [[nodiscard]] auto toLowerCase() const -> String;
  [[nodiscard]] auto toUpperCase() const -> String;
  [[nodiscard]] auto trim() const -> String;
  [[nodiscard]] auto toStdString() const -> std::string;
  [[nodiscard]] auto codePointAt(int32_t index) const -> int32_t;
  [[nodiscard]] auto codePointBefore(int32_t index) const -> int32_t;
  [[nodiscard]] auto codePointCount(int32_t beginIndex, int32_t endIndex) const
      -> int32_t;
  [[nodiscard]] auto indexOf(char ch) const -> int32_t;
  [[nodiscard]] auto indexOf(char ch, int32_t fromIndex) const -> int32_t;
  [[nodiscard]] auto indexOf(const String& str) const -> int32_t;
  [[nodiscard]] auto indexOf(const String& str, int32_t fromIndex) const
      -> int32_t;
  [[nodiscard]] auto lastIndexOf(char ch) const -> int32_t;
  [[nodiscard]] auto lastIndexOf(char ch, int32_t fromIndex) const -> int32_t;
  [[nodiscard]] auto lastIndexOf(const String& str) const -> int32_t;
  [[nodiscard]] auto lastIndexOf(const String& str, int32_t fromIndex) const
      -> int32_t;
  [[nodiscard]] auto matches(const std::string& regex) const -> bool;
  [[nodiscard]] auto replaceAll(const std::string& regex,
                                const std::string& replacement) const -> String;
  [[nodiscard]] auto replaceFirst(const std::string& regex,
                                  const std::string& replacement) const
      -> String;
  [[nodiscard]] auto split(const std::string& regex) const
      -> std::vector<String>;
  [[nodiscard]] auto split(const std::string& regex, int32_t limit) const
      -> std::vector<String>;
  static auto valueOf(bool b) -> String;
  static auto valueOf(char c) -> String;
  static auto valueOf(const char* data) -> String;
  static auto valueOf(int32_t i) -> String;
  static auto valueOf(int64_t l) -> String;
  static auto valueOf(float f) -> String;
  static auto valueOf(double d) -> String;
  static auto valueOf(const String& str) -> String;
  [[nodiscard]] auto regionMatches(int32_t tOffset, const String& other,
                                   int32_t oOffset, int32_t len) const -> bool;
  [[nodiscard]] auto regionMatches(bool ignoreCase, int32_t tOffset,
                                   const String& other, int32_t oOffset,
                                   int32_t len) const -> bool;
  auto operator<=>(const String& other) const -> std::partial_ordering;
  auto operator==(const String& other) const -> bool;
  auto operator+(const String& str) const -> String;

 private:
  friend std::formatter<String>;
  std::string value_{};
};
}  // namespace common

template <>
struct std::formatter<common::String>
    : common::GenericFormatter<common::String, &common::String::value_> {};
