#pragma once
#include <string>
#include <vector>

namespace common::toolkit {
    /// @brief A utility class for string manipulation operations.
    /// This class provides static methods for common string operations such as splitting and concatenating strings.
    class StringToolkit {
    public:
        StringToolkit() = delete;

        /// @brief Splits a string into a vector of strings based on a specified character.
        /// @param target The string to be split.
        /// @param split_char The character used as the delimiter for splitting.
        /// @return A vector of strings resulting from the split operation.
        [[nodiscard]] static auto split(const std::string &target, char split_char) -> std::vector<std::string>;

        /// @brief Splits a string into a vector of strings based on a specified character, including empty strings for consecutive delimiters.
        /// @param target The string to be split.
        /// @param split_char The character used as the delimiter for splitting.
        /// @return A vector of strings resulting from the split operation, including empty strings.
        [[nodiscard]] static auto splitWithEmpty(const std::string &target, char split_char) -> std::vector<std::string>;

        /// @brief Splits a string into a vector of strings based on a specified substring.
        /// @param target The string to be split.
        /// @param delimiter The substring used as the delimiter for splitting.
        /// @return A vector of strings resulting from the split operation.
        [[nodiscard]] static auto split(const std::string &target, const std::string &delimiter) -> std::vector<std::string>;

        /// @brief Concatenates a vector of strings into a single string with a specified character between each element.
        /// @param source The vector of strings to be concatenated.
        /// @param split_char The character to insert between each concatenated string.
        /// @return A single string composed of all elements in the vector separated by the specified character.
        [[nodiscard]] static auto concatenate(const std::vector<std::string> &source, char split_char) -> std::string;

        /// @brief Concatenates a vector of strings into a single string with a specified string between each element.
        /// @param source The vector of strings to be concatenated.
        /// @param delimiter The string to insert between each concatenated string.
        /// @return A single string composed of all elements in the vector separated by the specified string.
        [[nodiscard]] static auto concatenate(const std::vector<std::string> &source, const std::string &delimiter) -> std::string;

        /// @brief Checks if a string starts with a specified prefix.
        /// @param str The string to check.
        /// @param prefix The prefix to check for.
        /// @return true if the string starts with the prefix, false otherwise.
        [[nodiscard]] static auto startsWith(const std::string &str, const std::string &prefix) -> bool;

        /// @brief Checks if a string ends with a specified suffix.
        /// @param str The string to check.
        /// @param suffix The suffix to check for.
        /// @return true if the string ends with the suffix, false otherwise.
        [[nodiscard]] static auto endsWith(const std::string &str, const std::string &suffix) -> bool;

        /// @brief Trims whitespace from the beginning and end of a string.
        /// @param str The string to trim.
        /// @return A new string with whitespace removed from both ends.
        [[nodiscard]] static auto trim(const std::string &str) -> std::string;

        /// @brief Replaces all occurrences of a substring with another substring.
        /// @param str The string to perform replacements on.
        /// @param from The substring to replace.
        /// @param to The replacement substring.
        /// @return A new string with all occurrences replaced.
        [[nodiscard]] static auto replaceAll(const std::string &str, const std::string &from, const std::string &to) -> std::string;

        /// @brief Joins a vector of strings with a specified delimiter.
        /// @param parts The vector of strings to join.
        /// @param delimiter The string to insert between each part.
        /// @return A single joined string.
        [[nodiscard]] static auto join(const std::vector<std::string> &parts, const std::string &delimiter) -> std::string;
    };
}
