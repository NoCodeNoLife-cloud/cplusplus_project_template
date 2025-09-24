#pragma once
#include <string>
#include <vector>

namespace fox
{
    /// @brief A utility class for string manipulation operations.
    /// This class provides static methods for common string operations such as splitting and concatenating strings.
    class StringToolkit
    {
    public:
        StringToolkit() = delete;

        /// @brief Splits a string into a vector of strings based on a specified character.
        /// @param target The string to be split.
        /// @param split_char The character used as the delimiter for splitting.
        /// @return A vector of strings resulting from the split operation.
        [[nodiscard]] static auto split(const std::string& target,
                                        char split_char) noexcept -> std::vector<std::string>;

        /// @brief Concatenates a vector of strings into a single string with a specified character between each element.
        /// @param source The vector of strings to be concatenated.
        /// @param split_char The character to insert between each concatenated string.
        /// @return A single string composed of all elements in the vector separated by the specified character.
        [[nodiscard]] static auto concatenate(const std::vector<std::string>& source,
                                              char split_char) noexcept -> std::string;
    };

    inline auto StringToolkit::split(const std::string& target, const char split_char) noexcept -> std::vector<std::string>
    {
        std::vector<std::string> result;
        size_t start = 0;
        size_t pos = target.find(split_char);
        while (pos != std::string::npos)
        {
            result.push_back(target.substr(start, pos - start));
            start = pos + 1;
            pos = target.find(split_char, start);
        }
        result.push_back(target.substr(start));
        return result;
    }

    inline auto StringToolkit::concatenate(const std::vector<std::string>& source,
                                        const char split_char) noexcept -> std::string
    {
        if (source.empty())
            return "";
        std::string result = source[0];
        for (size_t i = 1; i < source.size(); ++i)
        {
            result += split_char;
            result += source[i];
        }
        return result;
    }
}
