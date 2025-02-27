#pragma once
#include <format>
#include <iostream>
#include <regex>
#include <string>
#include "Object.hpp"
#include "entity/interface/IComparable.hpp"

namespace common::entity::base_type
{
    class String final : public Object, iface::IComparable<String>
    {
    public:
        String();
        explicit String(const char* str);
        explicit String(std::string str);
        [[nodiscard]] auto charAt(int index) const -> char;
        [[nodiscard]] auto length() const -> size_t;
        [[nodiscard]] auto substring(int beginIndex, int endIndex) const -> String;
        [[nodiscard]] auto concat(const String& str) const -> String;
        [[nodiscard]] auto compareTo(const String& anotherString) const -> int override;
        [[nodiscard]] auto compareToIgnoreCase(const String& anotherString) const -> int;
        [[nodiscard]] auto isEmpty() const -> bool;
        [[nodiscard]] auto contains(const String& str) const -> bool;
        [[nodiscard]] auto replace(char oldChar, char newChar) const -> String;
        [[nodiscard]] auto toLowerCase() const -> String;
        [[nodiscard]] auto toUpperCase() const -> String;
        [[nodiscard]] auto trim() const -> String;
        [[nodiscard]] auto toStdString() const -> std::string;
        [[nodiscard]] auto equals(const String& other) const -> bool override;
        [[nodiscard]] auto codePointAt(int index) const -> int;
        [[nodiscard]] auto codePointBefore(int index) const -> int;
        [[nodiscard]] auto codePointCount(int beginIndex, int endIndex) const -> int;
        [[nodiscard]] auto indexOf(char ch) const -> int;
        [[nodiscard]] auto indexOf(char ch, int fromIndex) const -> int;
        [[nodiscard]] auto indexOf(const String& str) const -> int;
        [[nodiscard]] auto indexOf(const String& str, int fromIndex) const -> int;
        [[nodiscard]] auto lastIndexOf(char ch) const -> int;
        [[nodiscard]] auto lastIndexOf(char ch, int fromIndex) const -> int;
        [[nodiscard]] auto lastIndexOf(const String& str) const -> int;
        [[nodiscard]] auto lastIndexOf(const String& str, int fromIndex) const -> int;
        [[nodiscard]] auto matches(const std::string& regex) const -> bool;
        [[nodiscard]] auto replaceAll(const std::string& regex, const std::string& replacement) const -> String;
        [[nodiscard]] auto replaceFirst(const std::string& regex, const std::string& replacement) const -> String;
        [[nodiscard]] auto split(const std::string& regex) const -> std::vector<String>;
        [[nodiscard]] auto split(const std::string& regex, int limit) const -> std::vector<String>;
        static auto valueOf(bool b) -> String;
        static auto valueOf(char c) -> String;
        static auto valueOf(const char* data) -> String;
        static auto valueOf(int i) -> String;
        static auto valueOf(long l) -> String;
        static auto valueOf(float f) -> String;
        static auto valueOf(double d) -> String;
        static auto valueOf(const String& str) -> String;
        [[nodiscard]] auto regionMatches(int tOffset, const String& other, int oOffset, int len) const -> bool;
        [[nodiscard]] auto regionMatches(bool ignoreCase, int tOffset, const String& other, int oOffset, int len) const -> bool;
        auto operator==(const String& str) const -> bool;
        auto operator!=(const String& str) const -> bool;
        auto operator+(const String& str) const -> String;
        [[nodiscard]] auto toString() const -> std::string override;
    private:
        std::string data_{};
        friend std::formatter<String>;
    };

    inline String::String() = default;

    inline String::String(const char* str): data_(str) {}

    inline String::String(std::string str): data_(std::move(str)) {}

    inline auto String::charAt(const int index) const -> char
    {
        if (index < 0 || index >= data_.size()) throw std::out_of_range("Index out of bounds");
        return data_[index];
    }

    inline auto String::length() const -> size_t
    {
        return data_.size();
    }

    inline auto String::substring(const int beginIndex, const int endIndex) const -> String
    {
        if (beginIndex < 0 || endIndex > data_.size() || beginIndex > endIndex)
            throw std::out_of_range("Invalid range");
        return String(std::string(data_.substr(beginIndex, endIndex - beginIndex)));
    }

    inline auto String::concat(const String& str) const -> String
    {
        return String(std::string(data_ + str.data_));
    }

    inline auto String::compareTo(const String& anotherString) const -> int
    {
        return data_.compare(anotherString.data_);
    }

    inline auto String::compareToIgnoreCase(const String& anotherString) const -> int
    {
        std::string lower1 = data_, lower2 = anotherString.data_;
        std::ranges::transform(lower1, lower1.begin(), tolower);
        std::ranges::transform(lower2, lower2.begin(), tolower);
        return lower1.compare(lower2);
    }

    inline auto String::isEmpty() const -> bool
    {
        return data_.empty();
    }

    inline auto String::contains(const String& str) const -> bool
    {
        return data_.find(str.data_) != std::string::npos;
    }

    inline auto String::replace(const char oldChar, const char newChar) const -> String
    {
        std::string result = data_;
        std::ranges::replace(result, oldChar, newChar);
        return String(result);
    }

    inline auto String::toLowerCase() const -> String
    {
        std::string lower = data_;
        std::ranges::transform(lower, lower.begin(), tolower);
        return String(lower);
    }

    inline auto String::toUpperCase() const -> String
    {
        std::string upper = data_;
        std::ranges::transform(upper, upper.begin(), toupper);
        return String(upper);
    }

    inline auto String::trim() const -> String
    {
        const size_t start = data_.find_first_not_of(" \t\n\r");
        const size_t end = data_.find_last_not_of(" \t\n\r");
        if (start == std::string::npos) return String("");
        return String(data_.substr(start, end - start + 1));
    }

    inline auto String::toStdString() const -> std::string
    {
        return data_;
    }

    inline auto String::equals(const String& other) const -> bool
    {
        return data_ == other.data_;
    }

    inline auto String::codePointAt(const int index) const -> int
    {
        if (index < 0 || index >= data_.size()) throw std::out_of_range("Index out of bounds");
        return data_[index];
    }

    inline auto String::codePointBefore(const int index) const -> int
    {
        if (index <= 0 || index > data_.size()) throw std::out_of_range("Index out of bounds");
        return data_[index - 1];
    }

    inline auto String::codePointCount(const int beginIndex, const int endIndex) const -> int
    {
        if (beginIndex < 0 || endIndex > data_.size() || beginIndex > endIndex)
            throw std::out_of_range("Invalid range");
        return endIndex - beginIndex;
    }

    inline auto String::indexOf(const char ch) const -> int
    {
        const auto pos = data_.find(ch);
        return pos == std::string::npos ? -1 : static_cast<int>(pos);
    }

    inline auto String::indexOf(const char ch, const int fromIndex) const -> int
    {
        if (fromIndex < 0 || fromIndex >= data_.size()) throw std::out_of_range("Index out of bounds");
        const auto pos = data_.find(ch, fromIndex);
        return pos == std::string::npos ? -1 : static_cast<int>(pos);
    }

    inline auto String::indexOf(const String& str) const -> int
    {
        const auto pos = data_.find(str.data_);
        return pos == std::string::npos ? -1 : static_cast<int>(pos);
    }

    inline auto String::indexOf(const String& str, const int fromIndex) const -> int
    {
        if (fromIndex < 0 || fromIndex >= data_.size()) throw std::out_of_range("Index out of bounds");
        const auto pos = data_.find(str.data_, fromIndex);
        return pos == std::string::npos ? -1 : static_cast<int>(pos);
    }

    inline auto String::lastIndexOf(const char ch) const -> int
    {
        const auto pos = data_.rfind(ch);
        return pos == std::string::npos ? -1 : static_cast<int>(pos);
    }

    inline auto String::lastIndexOf(const char ch, const int fromIndex) const -> int
    {
        if (fromIndex < 0 || fromIndex >= data_.size()) throw std::out_of_range("Index out of bounds");
        const auto pos = data_.rfind(ch, fromIndex);
        return pos == std::string::npos ? -1 : static_cast<int>(pos);
    }

    inline auto String::lastIndexOf(const String& str) const -> int
    {
        const auto pos = data_.rfind(str.data_);
        return pos == std::string::npos ? -1 : static_cast<int>(pos);
    }

    inline auto String::lastIndexOf(const String& str, const int fromIndex) const -> int
    {
        if (fromIndex < 0 || fromIndex >= data_.size()) throw std::out_of_range("Index out of bounds");
        const auto pos = data_.rfind(str.data_, fromIndex);
        return pos == std::string::npos ? -1 : static_cast<int>(pos);
    }

    inline auto String::matches(const std::string& regex) const -> bool
    {
        return std::regex_match(data_, std::regex(regex));
    }

    inline auto String::replaceAll(const std::string& regex, const std::string& replacement) const -> String
    {
        return String(std::regex_replace(data_, std::regex(regex), replacement));
    }

    inline auto String::replaceFirst(const std::string& regex, const std::string& replacement) const -> String
    {
        const std::regex re(regex);
        std::string result = data_;
        if (std::smatch match; std::regex_search(result, match, re))
        {
            result.replace(match.position(0), match.length(0), replacement);
        }
        return String(result);
    }

    inline auto String::split(const std::string& regex) const -> std::vector<String>
    {
        const std::regex re(regex);
        std::sregex_token_iterator it(data_.begin(), data_.end(), re, -1);
        const std::sregex_token_iterator end;
        std::vector<String> result;
        while (it != end)
        {
            result.emplace_back(*it++);
        }
        return result;
    }

    inline auto String::split(const std::string& regex, const int limit) const -> std::vector<String>
    {
        const std::regex re(regex);
        std::sregex_token_iterator it(data_.begin(), data_.end(), re, -1);
        const std::sregex_token_iterator end;
        std::vector<String> result;
        while (it != end && (limit <= 0 || result.size() < static_cast<size_t>(limit - 1)))
        {
            result.emplace_back(*it++);
        }
        if (limit > 0 && it != end)
        {
            result.emplace_back(std::string(it->first, data_.end()));
        }
        return result;
    }

    inline auto String::valueOf(const bool b) -> String
    {
        return String(b ? "true" : "false");
    }

    inline auto String::valueOf(const char c) -> String
    {
        return String(std::string(1, c));
    }

    inline auto String::valueOf(const char* data) -> String
    {
        return String(data);
    }

    inline auto String::valueOf(const int i) -> String
    {
        return String(std::to_string(i));
    }

    inline auto String::valueOf(const long l) -> String
    {
        return String(std::to_string(l));
    }

    inline auto String::valueOf(const float f) -> String
    {
        return String(std::to_string(f));
    }

    inline auto String::valueOf(const double d) -> String
    {
        return String(std::to_string(d));
    }

    inline auto String::valueOf(const String& str) -> String
    {
        return str;
    }

    inline auto String::regionMatches(const int tOffset, const String& other, const int oOffset, const int len) const -> bool
    {
        if (tOffset < 0 || oOffset < 0 || tOffset + len > data_.size() || oOffset + len > other.data_.size())
        {
            return false;
        }
        return data_.compare(tOffset, len, other.data_, oOffset, len) == 0;
    }

    inline auto String::regionMatches(const bool ignoreCase, const int tOffset, const String& other, const int oOffset, const int len) const -> bool
    {
        if (!ignoreCase) return regionMatches(tOffset, other, oOffset, len);
        std::string thisRegion = data_.substr(tOffset, len);
        std::string otherRegion = other.data_.substr(oOffset, len);
        std::ranges::transform(thisRegion, thisRegion.begin(), tolower);
        std::ranges::transform(otherRegion, otherRegion.begin(), tolower);
        return thisRegion == otherRegion;
    }

    inline auto String::operator==(const String& str) const -> bool
    {
        return equals(str);
    }

    inline auto String::operator!=(const String& str) const -> bool
    {
        return !equals(str);
    }

    inline auto String::operator+(const String& str) const -> String
    {
        return this->concat(str);
    }

    inline std::string String::toString() const
    {
        return std::format("{}", *this);
    }
}

template <> struct std::formatter<common::entity::base_type::String>
{
    constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator
    {
        const auto begin = ctx.begin();
        if (const auto end = ctx.end(); begin != end && *begin != '}')
        {
            throw std::format_error("invalid format");
        }
        return begin;
    }

    static auto format(const common::entity::base_type::String& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>
    {
        return std::format_to(ctx.out(), "String{{data: {}}}", content.data_);
    }
};

inline auto operator<<(std::ostream& os, const common::entity::base_type::String& content) -> std::ostream&
{
    return os << std::format("{}", content);
}
