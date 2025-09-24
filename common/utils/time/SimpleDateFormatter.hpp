#pragma once
#include <functional>
#include <iomanip>
#include <sstream>
#include <string>
#include <stdexcept>

namespace fox
{
    /// @brief A utility class for formatting and parsing dates based on a pattern.
    /// The SimpleDateFormatter class provides methods to format std::tm objects into
    /// strings and parse strings back into std::tm objects using a specified pattern.
    /// It supports various date and time format specifiers similar to those used in
    /// strftime and strptime functions.
    class SimpleDateFormatter
    {
    public:
        explicit SimpleDateFormatter(const std::string& pattern);

        /// @brief Applies a new pattern to the date formatter.
        /// @param newPattern The new pattern to apply.
        auto applyPattern(const std::string& newPattern) -> void;

        /// @brief Retrieves the current pattern used by the date formatter.
        /// @return The current pattern as a string.
        [[nodiscard]] auto toPattern() const -> std::string;

        /// @brief Formats a given date according to the current pattern.
        /// @param date The date to format.
        /// @return The formatted date as a string.
        [[nodiscard]] auto format(const std::tm& date) const -> std::string;

        /// @brief Parses a date string according to the current pattern.
        /// @param dateStr The date string to parse.
        /// @return The parsed date as a std::tm structure.
        [[nodiscard]] auto parse(const std::string& dateStr) const -> std::tm;

        /// @brief Compares this formatter with another for equality.
        /// @param other The other formatter to compare with.
        /// @return True if both formatters are equal, false otherwise.
        [[nodiscard]] auto equals(const SimpleDateFormatter& other) const noexcept -> bool;

        /// @brief Computes the hash code for this formatter.
        /// @return The hash code as a size_t.
        [[nodiscard]] auto hashCode() const noexcept -> size_t;

    private:
        std::string pattern_;

        /// @brief Validates a given pattern string.
        /// @param pat The pattern to validate.
        static auto validatePattern(const std::string& pat) -> void;
    };

    inline SimpleDateFormatter::SimpleDateFormatter(const std::string& pattern)
    {
        validatePattern(pattern);
        pattern_ = pattern;
    }

    inline auto SimpleDateFormatter::applyPattern(const std::string& newPattern) -> void
    {
        validatePattern(newPattern);
        pattern_ = newPattern;
    }

    inline auto SimpleDateFormatter::toPattern() const -> std::string
    {
        return pattern_;
    }

    inline auto SimpleDateFormatter::format(const std::tm& date) const -> std::string
    {
        std::ostringstream oss;
        try
        {
            oss << std::put_time(&date, pattern_.c_str());
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error("Error formatting date: " + std::string(e.what()));
        }
        return oss.str();
    }

    inline auto SimpleDateFormatter::parse(const std::string& dateStr) const -> std::tm
    {
        std::istringstream iss(dateStr);
        std::tm date = {};
        try
        {
            iss >> std::get_time(&date, pattern_.c_str());
            if (iss.fail())
            {
                throw std::runtime_error("Failed to parse date: " + dateStr);
            }
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error("Error parsing date: " + std::string(e.what()));
        }
        return date;
    }

    inline auto SimpleDateFormatter::equals(const SimpleDateFormatter& other) const noexcept -> bool
    {
        return pattern_ == other.pattern_;
    }

    inline auto SimpleDateFormatter::hashCode() const noexcept -> size_t
    {
        return std::hash<std::string>{}(pattern_);
    }

    inline auto SimpleDateFormatter::validatePattern(const std::string& pat) -> void
    {
        if (pat.empty())
        {
            throw std::invalid_argument("Pattern cannot be empty.");
        }
    }
}
