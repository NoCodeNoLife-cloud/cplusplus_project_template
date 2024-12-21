#pragma once
#include <format>
#include <iostream>
#include <regex>
#include <string>
#include "Object.hpp"
#include "entity/interface/IfaceComparable.hpp"

namespace common::entity::base_type
{
    class String final : public Object, iface::IfaceComparable<String>
    {
    public:
        String() = default;

        explicit String(const char* str) : data_(str)
        {
        }

        explicit String(std::string str) : data_(std::move(str))
        {
        }

        [[nodiscard]] auto charAt(const int index) const -> char
        {
            if (index < 0 || index >= data_.size()) throw std::out_of_range("Index out of bounds");
            return data_[index];
        }

        [[nodiscard]] auto length() const -> size_t
        {
            return data_.size();
        }

        [[nodiscard]] auto substring(const int beginIndex, const int endIndex) const -> String
        {
            if (beginIndex < 0 || endIndex > data_.size() || beginIndex > endIndex)
                throw std::out_of_range(
                    "Invalid range");
            return String(std::string(data_.substr(beginIndex, endIndex - beginIndex)));
        }

        [[nodiscard]] auto concat(const String& str) const -> String
        {
            return String(std::string(data_ + str.data_));
        }

        [[nodiscard]] auto compareTo(const String& anotherString) const -> int override
        {
            return data_.compare(anotherString.data_);
        }

        [[nodiscard]] auto compareToIgnoreCase(const String& anotherString) const -> int
        {
            std::string lower1 = data_, lower2 = anotherString.data_;
            std::ranges::transform(lower1, lower1.begin(), tolower);
            std::ranges::transform(lower2, lower2.begin(), tolower);
            return lower1.compare(lower2);
        }

        [[nodiscard]] auto isEmpty() const -> bool
        {
            return data_.empty();
        }

        [[nodiscard]] auto contains(const String& str) const -> bool
        {
            return data_.find(str.data_) != std::string::npos;
        }

        [[nodiscard]] auto replace(const char oldChar, const char newChar) const -> String
        {
            std::string result = data_;
            std::ranges::replace(result, oldChar, newChar);
            return String(result);
        }

        [[nodiscard]] auto toLowerCase() const -> String
        {
            std::string lower = data_;
            std::ranges::transform(lower, lower.begin(), tolower);
            return String(lower);
        }

        [[nodiscard]] auto toUpperCase() const -> String
        {
            std::string upper = data_;
            std::ranges::transform(upper, upper.begin(), toupper);
            return String(upper);
        }

        [[nodiscard]] auto trim() const -> String
        {
            const size_t start = data_.find_first_not_of(" \t\n\r");
            const size_t end = data_.find_last_not_of(" \t\n\r");
            if (start == std::string::npos) return String("");
            return String(data_.substr(start, end - start + 1));
        }

        [[nodiscard]] auto toStdString() const -> std::string
        {
            return data_;
        }

        [[nodiscard]] auto equals(const String& other) const -> bool override
        {
            return data_ == other.data_;
        }

        [[nodiscard]] auto codePointAt(const int index) const -> int
        {
            if (index < 0 || index >= data_.size()) throw std::out_of_range("Index out of bounds");
            return data_[index];
        }

        [[nodiscard]] auto codePointBefore(const int index) const -> int
        {
            if (index <= 0 || index > data_.size()) throw std::out_of_range("Index out of bounds");
            return data_[index - 1];
        }

        [[nodiscard]] auto codePointCount(const int beginIndex, const int endIndex) const -> int
        {
            if (beginIndex < 0 || endIndex > data_.size() || beginIndex > endIndex)
                throw std::out_of_range(
                    "Invalid range");
            return endIndex - beginIndex;
        }

        [[nodiscard]] auto indexOf(const char ch) const -> int
        {
            const auto pos = data_.find(ch);
            return pos == std::string::npos ? -1 : static_cast<int>(pos);
        }

        [[nodiscard]] auto indexOf(const char ch, const int fromIndex) const -> int
        {
            if (fromIndex < 0 || fromIndex >= data_.size()) throw std::out_of_range("Index out of bounds");
            const auto pos = data_.find(ch, fromIndex);
            return pos == std::string::npos ? -1 : static_cast<int>(pos);
        }

        [[nodiscard]] auto indexOf(const String& str) const -> int
        {
            const auto pos = data_.find(str.data_);
            return pos == std::string::npos ? -1 : static_cast<int>(pos);
        }

        [[nodiscard]] auto indexOf(const String& str, const int fromIndex) const -> int
        {
            if (fromIndex < 0 || fromIndex >= data_.size()) throw std::out_of_range("Index out of bounds");
            const auto pos = data_.find(str.data_, fromIndex);
            return pos == std::string::npos ? -1 : static_cast<int>(pos);
        }

        [[nodiscard]] auto lastIndexOf(const char ch) const -> int
        {
            const auto pos = data_.rfind(ch);
            return pos == std::string::npos ? -1 : static_cast<int>(pos);
        }

        [[nodiscard]] auto lastIndexOf(const char ch, const int fromIndex) const -> int
        {
            if (fromIndex < 0 || fromIndex >= data_.size()) throw std::out_of_range("Index out of bounds");
            const auto pos = data_.rfind(ch, fromIndex);
            return pos == std::string::npos ? -1 : static_cast<int>(pos);
        }

        [[nodiscard]] auto lastIndexOf(const String& str) const -> int
        {
            const auto pos = data_.rfind(str.data_);
            return pos == std::string::npos ? -1 : static_cast<int>(pos);
        }

        [[nodiscard]] auto lastIndexOf(const String& str, const int fromIndex) const -> int
        {
            if (fromIndex < 0 || fromIndex >= data_.size()) throw std::out_of_range("Index out of bounds");
            const auto pos = data_.rfind(str.data_, fromIndex);
            return pos == std::string::npos ? -1 : static_cast<int>(pos);
        }

        [[nodiscard]] auto matches(const std::string& regex) const -> bool
        {
            return std::regex_match(data_, std::regex(regex));
        }

        [[nodiscard]] auto replaceAll(const std::string& regex, const std::string& replacement) const -> String
        {
            return String(std::regex_replace(data_, std::regex(regex), replacement));
        }

        [[nodiscard]] auto replaceFirst(const std::string& regex, const std::string& replacement) const -> String
        {
            const std::regex re(regex);
            std::string result = data_;
            if (std::smatch match; std::regex_search(result, match, re))
            {
                result.replace(match.position(0), match.length(0), replacement);
            }
            return String(result);
        }

        [[nodiscard]] auto split(const std::string& regex) const -> std::vector<String>
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

        [[nodiscard]] auto split(const std::string& regex, const int limit) const -> std::vector<String>
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

        static auto valueOf(const bool b) -> String
        {
            return String(b ? "true" : "false");
        }

        static auto valueOf(const char c) -> String
        {
            return String(std::string(1, c));
        }

        static auto valueOf(const char* data) -> String
        {
            return String(data);
        }

        static auto valueOf(const int i) -> String
        {
            return String(std::to_string(i));
        }

        static auto valueOf(const long l) -> String
        {
            return String(std::to_string(l));
        }

        static auto valueOf(const float f) -> String
        {
            return String(std::to_string(f));
        }

        static auto valueOf(const double d) -> String
        {
            return String(std::to_string(d));
        }

        static auto valueOf(const String& str) -> String
        {
            return str;
        }

        [[nodiscard]] auto regionMatches(const int tOffset, const String& other, const int oOffset,
                                         const int len) const -> bool
        {
            if (tOffset < 0 || oOffset < 0 || tOffset + len > data_.size() || oOffset + len > other.data_.size())
            {
                return false;
            }
            return data_.compare(tOffset, len, other.data_, oOffset, len) == 0;
        }

        [[nodiscard]] auto regionMatches(const bool ignoreCase, const int tOffset, const String& other,
                                         const int oOffset, const int len) const -> bool
        {
            if (!ignoreCase) return regionMatches(tOffset, other, oOffset, len);
            std::string thisRegion = data_.substr(tOffset, len);
            std::string otherRegion = other.data_.substr(oOffset, len);
            std::ranges::transform(thisRegion, thisRegion.begin(), tolower);
            std::ranges::transform(otherRegion, otherRegion.begin(), tolower);
            return thisRegion == otherRegion;
        }

        auto operator==(const String& str) const -> bool
        {
            return equals(str);
        }

        auto operator!=(const String& str) const -> bool
        {
            return !equals(str);
        }

        auto operator+(const String& str) const -> String
        {
            return this->concat(str);
        }

        [[nodiscard]] auto toString() const -> std::string override
        {
            return std::format("{}", *this);
        }

    private:
        std::string data_{};
        friend std::formatter<String>;
    };
}

template <>
struct std::formatter<common::entity::base_type::String>
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

    static auto format(const common::entity::base_type::String& content,
                       format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>
    {
        return std::format_to(ctx.out(), "String{{data: {}}}", content.data_);
    }
};

inline auto operator<<(std::ostream& os, const common::entity::base_type::String& content) -> std::ostream&
{
    return os << std::format("{}", content);
}
