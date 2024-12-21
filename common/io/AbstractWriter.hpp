#pragma once
#include <vector>
#include "interface/IfaceAppendable.hpp"
#include "interface/IfaceCloseable.hpp"
#include "interface/IfaceFlushable.hpp"

namespace common::io {
/// \brief Abstract class for objects that can be written to.
/// \details This class provides a basic interface for objects that can be written to.
/// It is used by the Writer class to provide a basic interface for writing to an output stream.
class AbstractWriter : public iface::IfaceCloseable, public iface::IfaceFlushable, iface::IfaceAppendable<AbstractWriter> {
public:
  AbstractWriter() = default;

  ~AbstractWriter() override = default;

  /// \brief Appends a character to the Writer.
  /// \details This method writes a single character to the writer object and returns a reference to the Writer.
  /// \param c The character to append.
  /// \return A reference to the Writer object.
  auto append(const char c) -> AbstractWriter& override {
    write(c);
    return *this;
  }

  /// \brief Appends a string to the Writer.
  /// \details This method writes the entire content of the given string to the writer object and returns a reference to the Writer.
  /// \param csq The string to append.
  /// \return A reference to the Writer object.
  auto append(const std::string& csq) -> AbstractWriter& override {
    write(csq);
    return *this;
  }

  /// \brief Appends a substring to the Writer.
  /// \details This method writes a substring of the given string to the writer object and returns a reference to the Writer.
  /// The substring is defined by the range [start, end).
  /// If the start or end indexes are out of bounds, or if start is greater than end,
  /// the function does nothing.
  /// \param csq The string from which a substring will be appended.
  /// \param start The starting index (inclusive) of the substring to append.
  /// \param end The ending index (exclusive) of the substring to append.
  /// \return A reference to the Writer object.
  auto append(const std::string& csq, const size_t start, const size_t end) -> AbstractWriter& override {
    write(csq, start, end);
    return *this;
  }

  /// \brief Writes a single character to the Writer.
  /// \details This method writes a single character to the writer object.
  /// It utilizes the overloaded write method to specify the starting position and length, writing a single character.
  /// \param c The character to write.
  virtual auto write(const char c) -> void {
    const std::vector buf(1, c);
    write(buf, 0, 1);
  }

  /// \brief Writes a vector of characters to the Writer.
  /// \details This method writes the entire content of the given vector of characters to the writer object.
  /// It utilizes the overloaded write method to specify the starting position and length, writing from the start to the end of the vector.
  /// \param cBuf The vector of characters to write.
  virtual auto write(const std::vector<char>& cBuf) -> void {
    write(cBuf, 0, cBuf.size());
  }

  virtual auto write(const std::vector<char>& cBuf, size_t off, size_t len) -> void = 0;

  /// \brief Writes a string to the Writer.
  /// \details This method writes the entire content of the given string to the writer object.
  /// It utilizes the overloaded write method to specify the starting position and length, writing from the start to the end of the string.
  /// \param str The string to write.
  virtual auto write(const std::string& str) -> void {
    write(str, 0, str.size());
  }

  /// \brief Writes a substring of the given string to the Writer.
  /// \details This method writes a substring of the given string to the writer object.
  /// The substring is defined by the range [start, end).
  /// If the start or end indexes are out of bounds, or if start is greater than end,
  /// the function does nothing.
  /// \param str The string from which a substring will be written.
  /// \param off The starting index (inclusive) of the substring to write.
  /// \param len The length of the substring to write.
  virtual auto write(const std::string& str, const size_t off, const size_t len) -> void {
    if (off < str.size()) {
      const size_t end = off + len < str.size() ? off + len : str.size();
      const std::vector buf(str.begin() + static_cast<std::string::difference_type>(off), str.begin() + static_cast<std::string::difference_type>(end));
      write(buf, 0, buf.size());
    }
  }

  [[nodiscard]] virtual auto toString() const -> std::string = 0;
};
}
