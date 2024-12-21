#pragma once
#include <format>
#include <iostream>
#include <string>
#include "interface/IfaceFlushable.hpp"

namespace common::io {
/// \brief A final class representing a console.
/// \details The Console class provides static methods for printing
/// to the standard output and reading from the standard input.
/// It is a final class that cannot be inherited from.
class Console final : public iface::IfaceFlushable {
public:
  /// \brief Prints a formatted string to the console.
  /// \details It prints a formatted string to the console using the provided format string and arguments.
  /// \param fmt The format string.
  /// \param args The arguments to format.
  template <typename... Args>
  auto format(const std::string& fmt, Args... args) -> void {
    std::cout << std::vformat(fmt, std::make_format_args(args...));
  }

  /// \brief Prints a formatted string to the console, followed by a newline.
  /// \details It prints a formatted string to the console using the provided format string and arguments,
  /// followed by a newline. It is equivalent to calling format(fmt, args...) followed by flush().
  template <typename... Args>
  auto printf(const std::string& fmt, Args... args) -> void {
    format(fmt, args...);
  }

  /// \brief Reads a line of input from the console.
  /// \details It reads a line of input from the console and returns it as a string.
  /// The line is read until a newline is encountered, and the newline is not included in the returned string.
  template <typename... Args>
  auto readLine(const std::string& fmt, Args... args) -> std::string {
    format(fmt, args...);
    return readLine();
  }

  /// \brief Flushes the output buffer.
  /// \details This function is a wrapper for std::cout.flush(). It is used to flush the output buffer of the console.
  auto flush() -> void override {
    std::cout.flush();
  }

  /// \brief Reads a line of text from the console.
  /// \details This function reads a line of text from the console and returns it as a string.
  /// The line is read until the end of line is reached or a maximum number of characters is read.
  static auto readLine() -> std::string {
    std::string input;
    std::getline(std::cin, input);
    return input;
  }

  /// \brief Gets the output stream used by the console.
  /// \details This function returns a reference to the output stream used by the console.
  /// The output stream is used to write to the console.
  static auto writer() -> std::ostream& {
    return std::cout;
  }

  /// \brief Gets the input stream used by the console.
  /// \details This function returns a reference to the input stream used by the console.
  /// The input stream is used to read from the console.
  static auto reader() -> std::istream& {
    return std::cin;
  }
};
}
