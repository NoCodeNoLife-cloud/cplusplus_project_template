#pragma once
#include <glog/logging.h>

#include <fstream>
#include <vector>

#include "AbstractWriter.hpp"

namespace fox {
/// @brief A buffered writer that writes data to an output stream with buffering.
/// This class provides efficient writing operations by buffering the output data
/// before writing it to the underlying output stream.
class BufferedWriter final : public AbstractWriter, public IAppendable<BufferedWriter> {
 public:
  explicit BufferedWriter(std::unique_ptr<std::ofstream> os, size_t size = DEFAULT_BUFFER_SIZE);
  ~BufferedWriter() override;

  /// @brief Writes a string to the buffer.
  /// @param str The string to write.
  auto write(const std::string& str) -> void override;

  /// @brief Writes a portion of a character buffer to the buffer.
  /// @param cBuf The character buffer to write from.
  /// @param off The offset in the buffer to start writing from.
  /// @param len The number of characters to write.
  auto write(const std::vector<char>& cBuf, size_t off, size_t len) -> void override;

  /// @brief Writes a newline character to the buffer.
  /// @return A reference to this BufferedWriter instance.
  auto newLine() -> BufferedWriter&;

  /// @brief Flushes the buffer to the underlying output stream.
  auto flush() -> void override;

  /// @brief Closes the writer and releases any resources.
  auto close() -> void override;

  /// @brief Appends a single character to the buffer.
  /// @param c The character to append.
  /// @return A reference to this BufferedWriter instance.
  auto append(char c) -> BufferedWriter& override;

  /// @brief Appends a string to the buffer.
  /// @param str The string to append.
  /// @return A reference to this BufferedWriter instance.
  auto append(const std::string& str) -> BufferedWriter& override;

  /// @brief Appends a substring to the buffer.
  /// @param str The string to append.
  /// @param start The starting index of the substring.
  /// @param end The ending index of the substring.
  /// @return A reference to this BufferedWriter instance.
  auto append(const std::string& str, size_t start, size_t end) -> BufferedWriter& override;

  /// @brief Converts the buffer content to a string representation.
  /// @return The string representation of the buffer content.
  [[nodiscard]] auto toString() const -> std::string override;

 private:
  static constexpr size_t DEFAULT_BUFFER_SIZE = 1024;
  std::unique_ptr<std::ofstream> output_stream_;
  std::vector<char> buffer_;
  size_t buffer_size_;
};
}  // namespace fox
