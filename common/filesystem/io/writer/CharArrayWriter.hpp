#pragma once
#include "AbstractWriter.hpp"

namespace common {
/// @brief A class for writing character data to a buffer in memory.
/// CharArrayWriter is a utility class that allows you to write character data
/// to an internal buffer. The buffer automatically expands as needed to hold
/// more data. You can retrieve the contents of the buffer as either a string
/// or a character array.
class CharArrayWriter final : public AbstractWriter, IAppendable<CharArrayWriter> {
 public:
  CharArrayWriter();
  explicit CharArrayWriter(int32_t initialSize);
  ~CharArrayWriter() override;

  /// @brief Writes a single character to the buffer.
  /// @param c The character to write.
  void write(char c) override;

  /// @brief Writes a portion of a character array to the buffer.
  /// @param cBuf The character array to write from.
  /// @param off The offset in the array to start writing from.
  /// @param len The number of characters to write.
  auto write(const std::vector<char>& cBuf, size_t off, size_t len) -> void override;

  /// @brief Writes a portion of a string to the buffer.
  /// @param str The string to write from.
  /// @param off The offset in the string to start writing from.
  /// @param len The number of characters to write.
  void write(const std::string& str, size_t off, size_t len) override;

  /// @brief Writes the contents of this writer to another writer.
  /// @param out The writer to write to.
  auto writeTo(AbstractWriter& out) const -> void;

  /// @brief Appends a string to the buffer.
  /// @param csq The string to append.
  /// @return A reference to this writer.
  CharArrayWriter& append(const std::string& csq) override;

  /// @brief Appends a subsequence of a string to the buffer.
  /// @param csq The string to append from.
  /// @param start The starting index of the subsequence.
  /// @param end The ending index of the subsequence.
  /// @return A reference to this writer.
  CharArrayWriter& append(const std::string& csq, size_t start, size_t end) override;

  /// @brief Appends a single character to the buffer.
  /// @param c The character to append.
  /// @return A reference to this writer.
  CharArrayWriter& append(char c) override;

  /// @brief Resets the buffer to empty.
  auto reset() -> void;

  /// @brief Returns a copy of the buffer's contents as a character array.
  /// @return A vector containing the buffer's contents.
  [[nodiscard]] auto toCharArray() const -> std::vector<char>;

  /// @brief Returns the current size of the buffer.
  /// @return The number of characters in the buffer.
  [[nodiscard]] auto size() const -> size_t;

  /// @brief Returns the buffer's contents as a string.
  /// @return A string representation of the buffer's contents.
  [[nodiscard]] auto toString() const -> std::string override;

  /// @brief Flushes the stream (no-op for this implementation).
  auto flush() -> void override;

  /// @brief Closes the writer (no-op for this implementation).
  auto close() -> void override;

 private:
  std::vector<char> buf_;
  size_t count_{0};
};
}  // namespace common
