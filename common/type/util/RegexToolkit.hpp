#pragma once

#include <regex>
#include <string>
#include <vector>
#include <stdexcept>

class RegexToolkit
{
public:
    /// @brief Checks if the entire string matches the regular expression
    /// @param text The string to check
    /// @param pattern The regular expression pattern
    /// @param flags Regular expression flags (default ECMAScript)
    /// @return true if the entire string matches the pattern, false otherwise
    /// @throws std::invalid_argument if the pattern is invalid
    static auto is_match(const std::string& text,
                         const std::string& pattern,
                         std::regex_constants::syntax_option_type flags = std::regex_constants::ECMAScript) -> bool;

    /// @brief Checks if there is a match for the regular expression anywhere in the string
    /// @param text The string to search
    /// @param pattern The regular expression pattern
    /// @param flags Regular expression flags (default ECMAScript)
    /// @return true if a match is found, false otherwise
    /// @throws std::invalid_argument if the pattern is invalid
    static auto is_search(const std::string& text,
                          const std::string& pattern,
                          std::regex_constants::syntax_option_type flags = std::regex_constants::ECMAScript) -> bool;

    /// @brief Extracts all matches of the regular expression in the string
    /// @param text The string to search
    /// @param pattern The regular expression pattern
    /// @param flags Regular expression flags (default ECMAScript)
    /// @return A vector containing all matched substrings
    /// @throws std::invalid_argument if the pattern is invalid
    static auto get_matches(const std::string& text,
                            const std::string& pattern,
                            std::regex_constants::syntax_option_type flags = std::regex_constants::ECMAScript) -> std::vector<std::string>;

    /// @brief Extracts all matches and their subgroups
    /// @param text The string to search
    /// @param pattern The regular expression pattern
    /// @param flags Regular expression flags (default ECMAScript)
    /// @return A vector of vectors containing matches and their subgroups
    /// @throws std::invalid_argument if the pattern is invalid
    static auto get_matches_with_groups(
        const std::string& text,
        const std::string& pattern,
        std::regex_constants::syntax_option_type flags = std::regex_constants::ECMAScript) -> std::vector<std::vector<std::string>>;

    /// @brief Replaces all matches of the regular expression with a replacement string
    /// @param text The string to process
    /// @param pattern The regular expression pattern
    /// @param replacement The replacement string
    /// @param flags Regular expression flags (default ECMAScript)
    /// @return The string with replacements made
    /// @throws std::invalid_argument if the pattern is invalid
    static auto replace_all(const std::string& text,
                            const std::string& pattern,
                            const std::string& replacement,
                            std::regex_constants::syntax_option_type flags = std::regex_constants::ECMAScript) -> std::string;

    /// @brief Splits a string by the regular expression delimiter
    /// @param text The string to split
    /// @param pattern The regular expression pattern for delimiters
    /// @param flags Regular expression flags (default ECMAScript)
    /// @return A vector containing the split parts
    /// @throws std::invalid_argument if the pattern is invalid
    static auto split(const std::string& text,
                      const std::string& pattern,
                      std::regex_constants::syntax_option_type flags = std::regex_constants::ECMAScript) -> std::vector<std::string>;
};

inline auto RegexToolkit::is_match(const std::string& text, const std::string& pattern, const std::regex_constants::syntax_option_type flags) -> bool
{
    try
    {
        const std::regex re(pattern, flags);
        return std::regex_match(text, re);
    }
    catch (const std::regex_error& e)
    {
        throw std::invalid_argument("Invalid regex pattern: " + std::string(e.what()));
    }
}

inline auto RegexToolkit::is_search(const std::string& text, const std::string& pattern, const std::regex_constants::syntax_option_type flags) -> bool
{
    try
    {
        const std::regex re(pattern, flags);
        return std::regex_search(text, re);
    }
    catch (const std::regex_error& e)
    {
        throw std::invalid_argument("Invalid regex pattern: " + std::string(e.what()));
    }
}

inline auto RegexToolkit::get_matches(const std::string& text, const std::string& pattern, std::regex_constants::syntax_option_type flags) -> std::vector<std::string>
{
    try
    {
        const std::regex re(pattern, flags);
        std::vector<std::string> results_;
        const auto it = std::sregex_iterator(text.begin(), text.end(), re);
        const auto end = std::sregex_iterator();

        for (auto i = it; i != end; ++i)
        {
            results_.push_back(i->str());
        }
        return results_;
    }
    catch (const std::regex_error& e)
    {
        throw std::invalid_argument("Invalid regex pattern: " + std::string(e.what()));
    }
}

inline auto RegexToolkit::get_matches_with_groups(const std::string& text, const std::string& pattern, std::regex_constants::syntax_option_type flags) -> std::vector<std::vector<std::string>>
{
    try
    {
        const std::regex re(pattern, flags);
        std::vector<std::vector<std::string>> results_;
        const auto it = std::sregex_iterator(text.begin(), text.end(), re);
        const auto end = std::sregex_iterator();

        for (auto i = it; i != end; ++i)
        {
            std::vector<std::string> groups_;
            for (size_t j = 0; j < i->size(); ++j)
            {
                groups_.push_back(i->str(j));
            }
            results_.push_back(groups_);
        }
        return results_;
    }
    catch (const std::regex_error& e)
    {
        throw std::invalid_argument("Invalid regex pattern: " + std::string(e.what()));
    }
}

inline auto RegexToolkit::replace_all(const std::string& text, const std::string& pattern, const std::string& replacement, const std::regex_constants::syntax_option_type flags) -> std::string
{
    try
    {
        const std::regex re(pattern, flags);
        return std::regex_replace(text, re, replacement);
    }
    catch (const std::regex_error& e)
    {
        throw std::invalid_argument("Invalid regex pattern: " + std::string(e.what()));
    }
}

inline auto RegexToolkit::split(const std::string& text, const std::string& pattern, const std::regex_constants::syntax_option_type flags) -> std::vector<std::string>
{
    try
    {
        const std::regex re(pattern, flags);
        std::sregex_token_iterator it(text.begin(), text.end(), re, -1);
        const std::sregex_token_iterator end;

        std::vector<std::string> results_;
        while (it != end)
        {
            results_.push_back(*it++);
        }
        return results_;
    }
    catch (const std::regex_error& e)
    {
        throw std::invalid_argument("Invalid regex pattern: " + std::string(e.what()));
    }
}
