#pragma once
#include <sstream>
#include <vector>

#include "AbstractWriter.hpp"

namespace common {
class StringWriter final : public AbstractWriter, public IAppendable<StringWriter> {
 public:
  explicit StringWriter(size_t initialSize);
  ~StringWriter() override;

  /// @brief Appends the specified character to this writer.
  /// @param c The character to append.
  /// @return A reference to this StringWriter.
  auto append(char c) -> StringWriter& override;

  /// @brief Appends the specified string to this writer.
  /// @param csq The string to append.
  /// @return A reference to this StringWriter.
  auto append(const std::string& csq) -> StringWriter& override;

  /// @brief Appends a subsequence of the specified string to this writer.
  /// @param csq The string from which a subsequence is appended.
  /// @param start The starting index of the subsequence.
  /// @param end The ending index of the subsequence.
  /// @return A reference to this StringWriter.
  auto append(const std::string& csq, size_t start, size_t end) -> StringWriter& override;

  /// @brief Closes the writer and releases any associated resources.
  auto close() -> void override;

  /// @brief Flushes the writer, ensuring all buffered data is written.
  auto flush() -> void override;

  /// @brief Gets the current buffer content as a string.
  /// @return The buffer content.
  [[nodiscard]] auto getBuffer() const -> std::string;

  /// @brief Converts the buffer content to a string representation.
  /// @return The string representation of the buffer.
  [[nodiscard]] auto toString() const -> std::string override;

  /// @brief Writes a single character to the writer.
  /// @param c The character to write.
  auto write(char c) -> void override;

  /// @brief Writes the specified string to the writer.
  /// @param str The string to write.
  auto write(const std::string& str) -> void override;

  /// @brief Writes a portion of the specified string to the writer.
  /// @param str The string to write.
  /// @param off The offset from which to start writing.
  /// @param len The number of characters to write.
  auto write(const std::string& str, size_t off, size_t len) -> void override;

  /// @brief Writes a portion of the specified character array to the writer.
  /// @param cBuf The character array to write.
  /// @param off The offset from which to start writing.
  /// @param len The number of characters to write.
  auto write(const std::vector<char>& cBuf, size_t off, size_t len) -> void override;

 private:
  std::ostringstream buffer_;
};
}  // namespace common
