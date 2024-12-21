#pragma once
#include "File.hpp"
#include "FilterOutputStream.hpp"
#include "interface/IfaceAppendable.hpp"

namespace common::io {
/// \brief A class that provides methods to print data to an output stream.
/// \details The PrintStream class provides methods to print data to an output stream.
/// It is a concrete implementation of the FilterOutputStream and IfaceAppendable interfaces.
/// It supports printing of various types of data, including boolean, character, integer, long, float, double,
/// string, and vector of characters. It also supports flushing and closing the stream.
class PrintStream final : public FilterOutputStream, public iface::IfaceAppendable<PrintStream> {
public:
  PrintStream(std::shared_ptr<AbstractOutputStream> outStream, const bool autoFlush, const std::locale& loc): FilterOutputStream(std::move(outStream)), autoFlush_(autoFlush), locale_(loc) {}

  ~PrintStream() override = delete;

  /// \brief Appends a character to the stream.
  /// \details Writes the character to the stream and flushes if needed.
  /// \param c The character to append.
  auto append(char c) -> PrintStream& override {
    write(static_cast<std::byte>(c));
    flushIfNeeded();
    return *this;
  }

  /// \brief Appends a string to the stream.
  /// \details Writes the string to the stream and flushes if needed.
  /// \param str The string to append.
  auto append(const std::string& str) -> PrintStream& override {
    for (char c : str) {
      write(static_cast<std::byte>(c));
    }
    flushIfNeeded();
    return *this;
  }

  /// \brief Appends a substring to the stream.
  /// \details Writes the substring to the stream and flushes if needed.
  /// \param str The string to append.
  /// \param start The start of the substring.
  /// \param end The end of the substring.
  auto append(const std::string& str, size_t start, size_t end) -> PrintStream& override {
    for (size_t i = start; i < end; i++) {
      write(static_cast<std::byte>(str[i]));
    }
    flushIfNeeded();
    return *this;
  }

  /// \brief Prints a boolean value to the stream.
  /// \details Writes the boolean value to the stream and flushes if needed.
  /// \param b The boolean value to print.
  auto print(const bool b) const -> void {
    if (outputStream_) {
      outputStream_->write(static_cast<std::byte>(b ? 1 : 0));
    }
    flushIfNeeded();
  }

  /// \brief Prints a character to the stream.
  /// \details Writes the character to the stream and flushes if needed.
  /// \param c The character to print.
  auto print(char c) const -> void {
    if (outputStream_) {
      outputStream_->write(static_cast<std::byte>(c));
      flushIfNeeded();
    }
  }

  /// \brief Prints an integer value to the stream.
  /// \details Writes the integer value to the stream and flushes if needed.
  /// \param i The integer value to print.
  auto print(const int i) const -> void {
    if (outputStream_) {
      for (const auto buffer = std::to_string(i); char c : buffer) {
        outputStream_->write(static_cast<std::byte>(c));
      }
      flushIfNeeded();
    }
  }

  /// \brief Prints a long value to the stream.
  /// \details Writes the long value to the stream and flushes if needed.
  /// \param l The long value to print.
  auto print(const long l) const -> void {
    if (outputStream_) {
      for (const auto buffer = std::to_string(l); char c : buffer) {
        outputStream_->write(static_cast<std::byte>(c));
      }
      flushIfNeeded();
    }
  }

  /// \brief Prints a float value to the stream.
  /// \details Writes the float value to the stream and flushes if needed.
  /// \param f The float value to print.
  auto print(const float f) const -> void {
    if (outputStream_) {
      for (const auto buffer = std::to_string(f); char c : buffer) {
        outputStream_->write(static_cast<std::byte>(c));
      }
      flushIfNeeded();
    }
  }

  /// \brief Prints a double value to the stream.
  /// \details Writes the double value to the stream and flushes if needed.
  /// \param d The double value to print.
  auto print(const double d) const -> void {
    if (outputStream_) {
      for (const auto buffer = std::to_string(d); char c : buffer) {
        outputStream_->write(static_cast<std::byte>(c));
      }
      flushIfNeeded();
    }
  }

  /// \brief Prints a string to the stream.
  /// \details Writes the string to the stream and flushes if needed.
  /// \param s The string to print.
  auto print(const char* s) const -> void {
    if (outputStream_ && s) {
      while (*s) {
        outputStream_->write(static_cast<std::byte>(*s++));
      }
      flushIfNeeded();
    }
  }

  /// \brief Prints a string to the stream.
  /// \details Writes the string to the stream and flushes if needed.
  /// \param s The string to print.
  auto print(const std::string& s) const -> void {
    if (outputStream_) {
      for (char c : s) {
        outputStream_->write(static_cast<std::byte>(c));
      }
      flushIfNeeded();
    }
  }

  /// \brief Prints a vector of characters to the stream.
  /// \details Writes the vector of characters to the stream and flushes if needed.
  /// \param v The vector of characters to print.
  auto print(const std::vector<char>& v) const -> void {
    if (outputStream_) {
      for (char c : v) {
        outputStream_->write(static_cast<std::byte>(c));
      }
      flushIfNeeded();
    }
  }

  /// \brief Prints a boolean value to the stream.
  /// \details Writes the boolean value to the stream and flushes if needed.
  /// \param b The boolean value to print.
  auto println(const bool b) const -> void {
    print(b);
    print('\n');
  }

  /// \brief Prints a character to the stream.
  /// \details Writes the character to the stream and flushes if needed.
  /// \param c The character to print.
  auto println(const char c) const -> void {
    print(c);
    print('\n');
  }

  /// \brief Prints an integer value to the stream.
  /// \details Writes the integer value to the stream and flushes if needed.
  /// \param i The integer value to print.
  auto println(const int i) const -> void {
    print(i);
    print('\n');
  }

  /// \brief Prints a long value to the stream.
  /// \details Writes the long value to the stream and flushes if needed.
  /// \param l The long value to print.
  auto println(long l) const -> void {
    print(l);
    print('\n');
  }

  /// \brief Prints a float value followed by a newline to the stream.
  /// \details Writes the float value to the stream, appends a newline character, and flushes if needed.
  /// \param f The float value to print.
  auto println(float f) const -> void {
    print(f);
    print('\n');
  }

  /// \brief Prints a double value followed by a newline to the stream.
  /// \details Writes the double value to the stream, appends a newline character, and flushes if needed.
  /// \param d The double value to print.
  auto println(double d) const -> void {
    print(d);
    print('\n');
  }

  /// \brief Prints a string followed by a newline to the stream.
  /// \details Writes the string to the stream, appends a newline character, and flushes if needed.
  /// \param s The string to print.
  auto println(const char* s) const -> void {
    print(s);
    print('\n');
  }

  /// \brief Prints a string followed by a newline to the stream.
  /// \details Writes the string to the stream, appends a newline character, and flushes if needed.
  /// \param s The string to print.
  auto println(const std::string& s) const -> void {
    print(s);
    print('\n');
  }

  /// \brief Prints a vector of characters followed by a newline to the stream.
  /// \details Writes the vector of characters to the stream, appends a newline character, and flushes if needed.
  /// \param v The vector of characters to print.
  auto println(const std::vector<char>& v) const -> void {
    print(v);
    print('\n');
  }

  /// \brief Flushes the stream.
  /// \details Flushes the internal buffer of the output stream.
  auto flush() -> void override {
    if (outputStream_) {
      outputStream_->flush();
    }
  }

  /// \brief Closes the stream and its underlying stream.
  /// \details Closes the stream by closing the underlying output stream.
  auto close() -> void override {
    if (outputStream_) {
      outputStream_->close();
    }
  }

protected:
  bool autoFlush_{false};
  bool errorState_{false};
  std::locale locale_;

  /// \brief Flushes the stream if autoFlush is enabled.
  /// \details Flushes the internal buffer of the output stream if autoFlush is enabled.
  auto flushIfNeeded() const -> void {
    if (autoFlush_ && outputStream_) {
      outputStream_->flush();
    }
  }
};
}
