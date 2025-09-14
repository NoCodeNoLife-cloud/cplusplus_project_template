#pragma once
#include <format>
#include <iostream>
#include <string>

#include "interface/IFlushable.hpp"

namespace fox
{
/// @brief Provides console input/output operations with formatting capabilities.
/// This class implements the IFlushable interface and offers methods for formatted
/// output, input reading, and stream management.
class Console final : public IFlushable
{
  public:
    /// @brief Formats and prints a string to the console.
    /// @tparam Args Variadic template arguments.
    /// @param fmt The format string.
    /// @param args Arguments to be formatted.
    template <typename... Args> auto format(const std::string &fmt, Args... args) -> void
    {
        std::cout << std::vformat(fmt, std::make_format_args(args...));
    }

    /// @brief Prints a formatted string to the console.
    /// @tparam Args Variadic template arguments.
    /// @param fmt The format string.
    /// @param args Arguments to be formatted.
    template <typename... Args> auto printf(const std::string &fmt, Args... args) -> void
    {
        format(fmt, args...);
    }

    /// @brief Reads a line from the console with a prompt.
    /// @tparam Args Variadic template arguments for the prompt formatting.
    /// @param fmt The format string for the prompt.
    /// @param args Arguments to be formatted in the prompt.
    /// @return The read line as a string.
    template <typename... Args> auto readLine(const std::string &fmt, Args... args) -> std::string
    {
        format(fmt, args...);
        return readLine();
    }

    /// @brief Flushes the console output.
    auto flush() -> void override
    {
        std::cout.flush();
    }

    /// @brief Reads a line from the console.
    /// @return The read line as a string.
    static auto readLine() -> std::string
    {
        std::string input;
        std::getline(std::cin, input);
        return input;
    }

    /// @brief Gets the writer stream for the console.
    /// @return Reference to the output stream.
    static auto writer() -> std::ostream &
    {
        return std::cout;
    }

    /// @brief Gets the reader stream for the console.
    /// @return Reference to the input stream.
    static auto reader() -> std::istream &
    {
        return std::cin;
    }
};
} // namespace fox