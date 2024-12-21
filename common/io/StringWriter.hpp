#pragma once
#include <sstream>
#include <vector>
#include "AbstractWriter.hpp"
#include "interface/IfaceAppendable.hpp"

namespace common::io {
/// \brief A final class for writing characters to a string buffer.
/// \details The StringWriter class provides methods to write data to an internal string buffer.
/// It implements the Closeable, Flushable, and Appendable interfaces.
/// The class allows appending characters and strings, as well as flushing and closing operations.
/// It is useful for accumulating strings into a single string buffer and then retrieving the full content.
class StringWriter final : public AbstractWriter, public iface::IfaceAppendable<StringWriter> {
public:
  explicit StringWriter(const size_t initialSize) {
    // Reserve an approximate initial size for the string buffer.
    buffer_.str(std::string(initialSize, '\0'));
    buffer_.seekp(0); // Reset the write position to the start.
  }

  ~StringWriter() override = default;

  /// \brief Appends a single character to the writer.
  /// \details This method appends the character to the internal string buffer.
  /// \return The writer object, allowing method chaining.
  auto append(const char c) -> StringWriter& override {
    buffer_.put(c);
    return *this;
  }

  /// \brief Appends a string to the writer.
  /// \details This method appends the entire string to the internal string buffer.
  /// \return The writer object, allowing method chaining.
  auto append(const std::string& csq) -> StringWriter& override {
    buffer_ << csq;
    return *this;
  }

  /// \brief Appends a substring to the writer.
  /// \details This method appends the characters of the substring of the given string,
  /// starting at \p start and ending at \p end, to the internal string buffer.
  /// If the start or end indexes are out of bounds, or if start is greater than end,
  /// a std::out_of_range exception is thrown.
  /// \param csq The string from which a substring will be appended.
  /// \param start The starting index (inclusive) of the substring to append.
  /// \param end The ending index (exclusive) of the substring to append.
  /// \return A reference to the StringWriter object.
  auto append(const std::string& csq, const size_t start, const size_t end) -> StringWriter& override {
    if (start > end || end > csq.size()) {
      throw std::out_of_range("Invalid start or end position");
    }
    buffer_.write(csq.data() + start, static_cast<std::streamsize>(end - start));
    return *this;
  }

  /// \brief Closes the writer, releasing any system resources associated with it.
  /// \details This method has no effect; it is a no-op.
  auto close() -> void override {
    // No operation; closing is a no-op.
  }

  /// \brief Flushes the internal buffer.
  /// \details This method flushes the underlying string buffer,
  /// ensuring that all buffered output is written out.
  /// It is a no-op for std::ostringstream, as it does not require flushing.
  auto flush() -> void override {
    buffer_.flush();
  }

  /// \brief Retrieves the current contents of the buffer.
  /// \details This function returns the current contents of the internal string buffer
  /// as a std::string. It provides a snapshot of the data accumulated in the buffer.
  [[nodiscard]] auto getBuffer() const -> std::string {
    return buffer_.str();
  }

  /// \brief Converts the writer to a string.
  /// \details This function returns a string representation of the writer.
  /// It is equivalent to calling `getBuffer()`.
  /// \return The string representation of the writer.
  [[nodiscard]] auto toString() const -> std::string override {
    return buffer_.str();
  }

  /// \brief Writes a single character to the writer.
  /// \details This function writes a single character to the internal string buffer.
  /// \param c the character to write.
  auto write(const char c) -> void override {
    buffer_.put(c);
  }

  /// \brief Writes a string to the writer.
  /// \details This function writes the contents of the provided string to the writer.
  /// \param str the string to write.
  auto write(const std::string& str) -> void override {
    buffer_ << str;
  }

  /// \brief Writes a substring of the given string to the writer.
  /// \details This function writes a substring of the given string to the writer.
  /// The substring is defined by the range [start, end).
  /// If the start or end indexes are out of bounds, or if start is greater than end,
  /// a std::out_of_range exception is thrown.
  /// \param str the string from which a substring will be written.
  /// \param off the starting index (inclusive) of the substring to write.
  /// \param len the length of the substring to write.
  auto write(const std::string& str, const size_t off, const size_t len) -> void override {
    if (off > str.size() || off + len > str.size()) {
      throw std::out_of_range("Invalid offset or length");
    }
    buffer_.write(str.data() + off, static_cast<std::streamsize>(len));
  }

  /// \brief Writes a portion of the byte array to the writer.
  /// \details This function writes a portion of the given byte array to the writer.
  /// The portion is defined by the range [off, off+len).
  /// If the offset and length are out of bounds of the byte array,
  /// a std::out_of_range exception is thrown.
  /// \param cBuf the byte array to write.
  /// \param off the starting index (inclusive) of the portion to write.
  /// \param len the length of the portion to write.
  auto write(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void override {
    if (off > cBuf.size() || len > cBuf.size() - off) {
      throw std::out_of_range("Invalid offset or length");
    }
    buffer_.write(cBuf.data() + off, static_cast<std::streamsize>(len));
  }

private:
  std::ostringstream buffer_;
};
}
