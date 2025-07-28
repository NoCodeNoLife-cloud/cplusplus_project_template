#include <boost/functional/hash.hpp>
#include <regex>
// this "String.hpp" must here
#include "String.hpp"

namespace common {
String::String() = default;
String::~String() = default;

String::String(const char* str) : value_(str) {}

String::String(std::string str) : value_(std::move(str)) {}

String::String(const String& other) : value_(other.value_) {}

String::String(String&& other) noexcept
    : value_(other.value_) {}  // NOLINT(*-move-constructor-init)
String& String::operator=(const String& other) {
  if (this != &other) {
    value_ = other.value_;
  }
  return *this;
}

String& String::operator=(String&& other) noexcept {
  if (this != &other) {
    value_ = other.value_;
  }
  return *this;
}

String::operator std::string() const { return value_; }

size_t String::hashCode() const {
  size_t seed = 0;
  boost::hash_combine(seed, getClass());
  boost::hash_combine(seed, value_);
  return seed;
}

std::string String::toString() const { return std::format("{}", *this); }

auto String::charAt(const int32_t index) const -> char {
  if (index < 0 || index >= value_.size())
    throw std::out_of_range("Index out of bounds");
  return value_[index];
}

auto String::length() const -> size_t { return value_.size(); }

auto String::substring(const int32_t beginIndex, const int32_t endIndex) const
    -> String {
  if (beginIndex < 0 || endIndex > value_.size() || beginIndex > endIndex)
    throw std::out_of_range("Invalid range");
  return String(std::string(value_.substr(beginIndex, endIndex - beginIndex)));
}

auto String::concat(const String& str) const -> String {
  return String(std::string(value_ + str.value_));
}

auto String::compareToIgnoreCase(const String& anotherString) const -> int32_t {
  std::string lower1 = value_, lower2 = anotherString.value_;
  std::ranges::transform(lower1, lower1.begin(), tolower);
  std::ranges::transform(lower2, lower2.begin(), tolower);
  return lower1.compare(lower2);
}

auto String::isEmpty() const -> bool { return value_.empty(); }

auto String::contains(const String& str) const -> bool {
  return value_.find(str.value_) != std::string::npos;
}

auto String::replace(const char oldChar, const char newChar) const -> String {
  std::string result = value_;
  std::ranges::replace(result, oldChar, newChar);
  return String(result);
}

auto String::toLowerCase() const -> String {
  std::string lower = value_;
  std::ranges::transform(lower, lower.begin(), tolower);
  return String(lower);
}

auto String::toUpperCase() const -> String {
  std::string upper = value_;
  std::ranges::transform(upper, upper.begin(), toupper);
  return String(upper);
}

auto String::trim() const -> String {
  const size_t start = value_.find_first_not_of(" \t\n\r");
  const size_t end = value_.find_last_not_of(" \t\n\r");
  if (start == std::string::npos) return String("");
  return String(value_.substr(start, end - start + 1));
}

auto String::toStdString() const -> std::string { return value_; }

auto String::codePointAt(const int32_t index) const -> int32_t {
  if (index < 0 || index >= value_.size())
    throw std::out_of_range("Index out of bounds");
  return value_[index];
}

auto String::codePointBefore(const int32_t index) const -> int32_t {
  if (index <= 0 || index > value_.size())
    throw std::out_of_range("Index out of bounds");
  return value_[index - 1];
}

auto String::codePointCount(const int32_t beginIndex,
                            const int32_t endIndex) const -> int32_t {
  if (beginIndex < 0 || endIndex > value_.size() || beginIndex > endIndex)
    throw std::out_of_range("Invalid range");
  return endIndex - beginIndex;
}

auto String::indexOf(const char ch) const -> int32_t {
  const auto pos = value_.find(ch);
  return pos == std::string::npos ? -1 : static_cast<int32_t>(pos);
}

auto String::indexOf(const char ch, const int32_t fromIndex) const -> int32_t {
  if (fromIndex < 0 || fromIndex >= value_.size())
    throw std::out_of_range("Index out of bounds");
  const auto pos = value_.find(ch, fromIndex);
  return pos == std::string::npos ? -1 : static_cast<int32_t>(pos);
}

auto String::indexOf(const String& str) const -> int32_t {
  const auto pos = value_.find(str.value_);
  return pos == std::string::npos ? -1 : static_cast<int32_t>(pos);
}

auto String::indexOf(const String& str, const int32_t fromIndex) const
    -> int32_t {
  if (fromIndex < 0 || fromIndex >= value_.size())
    throw std::out_of_range("Index out of bounds");
  const auto pos = value_.find(str.value_, fromIndex);
  return pos == std::string::npos ? -1 : static_cast<int32_t>(pos);
}

auto String::lastIndexOf(const char ch) const -> int32_t {
  const auto pos = value_.rfind(ch);
  return pos == std::string::npos ? -1 : static_cast<int32_t>(pos);
}

auto String::lastIndexOf(const char ch, const int32_t fromIndex) const
    -> int32_t {
  if (fromIndex < 0 || fromIndex >= value_.size())
    throw std::out_of_range("Index out of bounds");
  const auto pos = value_.rfind(ch, fromIndex);
  return pos == std::string::npos ? -1 : static_cast<int32_t>(pos);
}

auto String::lastIndexOf(const String& str) const -> int32_t {
  const auto pos = value_.rfind(str.value_);
  return pos == std::string::npos ? -1 : static_cast<int32_t>(pos);
}

auto String::lastIndexOf(const String& str, const int32_t fromIndex) const
    -> int32_t {
  if (fromIndex < 0 || fromIndex >= value_.size())
    throw std::out_of_range("Index out of bounds");
  const auto pos = value_.rfind(str.value_, fromIndex);
  return pos == std::string::npos ? -1 : static_cast<int32_t>(pos);
}

auto String::matches(const std::string& regex) const -> bool {
  return std::regex_match(value_, std::regex(regex));
}

auto String::replaceAll(const std::string& regex,
                        const std::string& replacement) const -> String {
  return String(std::regex_replace(value_, std::regex(regex), replacement));
}

auto String::replaceFirst(const std::string& regex,
                          const std::string& replacement) const -> String {
  const std::regex re(regex);
  std::string result = value_;
  if (std::smatch match; std::regex_search(result, match, re)) {
    result.replace(match.position(0), match.length(0), replacement);
  }
  return String(result);
}

auto String::split(const std::string& regex) const -> std::vector<String> {
  const std::regex re(regex);
  std::sregex_token_iterator it(value_.begin(), value_.end(), re, -1);
  const std::sregex_token_iterator end;
  std::vector<String> result;
  while (it != end) {
    result.emplace_back(*it++);
  }
  return result;
}

auto String::split(const std::string& regex, const int32_t limit) const
    -> std::vector<String> {
  const std::regex re(regex);
  std::sregex_token_iterator it(value_.begin(), value_.end(), re, -1);
  const std::sregex_token_iterator end;
  std::vector<String> result;
  while (it != end &&
         (limit <= 0 || result.size() < static_cast<size_t>(limit - 1))) {
    result.emplace_back(*it++);
  }
  if (limit > 0 && it != end) {
    result.emplace_back(std::string(it->first, value_.end()));
  }
  return result;
}

auto String::valueOf(const bool b) -> String {
  return String(b ? "true" : "false");
}

auto String::valueOf(const char c) -> String {
  return String(std::string(1, c));
}

auto String::valueOf(const char* data) -> String { return String(data); }

auto String::valueOf(const int32_t i) -> String {
  return String(std::to_string(i));
}

auto String::valueOf(const int64_t l) -> String {
  return String(std::to_string(l));
}

auto String::valueOf(const float f) -> String {
  return String(std::to_string(f));
}

auto String::valueOf(const double d) -> String {
  return String(std::to_string(d));
}

auto String::valueOf(const String& str) -> String { return str; }

auto String::regionMatches(const int32_t tOffset, const String& other,
                           const int32_t oOffset, const int32_t len) const
    -> bool {
  if (tOffset < 0 || oOffset < 0 || tOffset + len > value_.size() ||
      oOffset + len > other.value_.size()) {
    return false;
  }
  return value_.compare(tOffset, len, other.value_, oOffset, len) == 0;
}

auto String::regionMatches(const bool ignoreCase, const int32_t tOffset,
                           const String& other, const int32_t oOffset,
                           const int32_t len) const -> bool {
  if (!ignoreCase) return regionMatches(tOffset, other, oOffset, len);
  std::string thisRegion = value_.substr(tOffset, len);
  std::string otherRegion = other.value_.substr(oOffset, len);
  std::ranges::transform(thisRegion, thisRegion.begin(), tolower);
  std::ranges::transform(otherRegion, otherRegion.begin(), tolower);
  return thisRegion == otherRegion;
}

auto String::operator<=>(const String& other) const -> std::partial_ordering {
  return value_ <=> other.value_;
}

auto String::operator==(const String& other) const -> bool {
  return value_ == other.value_;
}

auto String::operator+(const String& str) const -> String {
  return this->concat(str);
}
}  // namespace common
