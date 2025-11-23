#include "src/toolkit/RegexToolkit.hpp"

#include <regex>
#include <string>
#include <vector>
#include <stdexcept>

namespace common
{
    auto RegexToolkit::is_match(const std::string& text,
                                const std::string& pattern,
                                const std::regex_constants::syntax_option_type flags)
        -> bool
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

    auto RegexToolkit::is_search(const std::string& text,
                                 const std::string& pattern,
                                 const std::regex_constants::syntax_option_type flags)
        -> bool
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

    auto RegexToolkit::get_matches(const std::string& text,
                                   const std::string& pattern,
                                   std::regex_constants::syntax_option_type flags)
        -> std::vector<std::string>
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

    auto RegexToolkit::get_matches_with_groups(const std::string& text,
                                               const std::string& pattern,
                                               std::regex_constants::syntax_option_type flags)
        -> std::vector<std::vector<std::string>>
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

    auto RegexToolkit::replace_all(const std::string& text,
                                   const std::string& pattern,
                                   const std::string& replacement,
                                   const std::regex_constants::syntax_option_type flags)
        -> std::string
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

    auto RegexToolkit::split(const std::string& text,
                             const std::string& pattern,
                             const std::regex_constants::syntax_option_type flags)
        -> std::vector<std::string>
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
}
