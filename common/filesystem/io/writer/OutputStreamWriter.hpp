#pragma once
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#include <codecvt>

#include "AbstractWriter.hpp"

namespace fox {
/// @brief A writer that converts character streams to byte streams using a specified charset
/// OutputStreamWriter is a bridge from character streams to byte streams: Characters written to it
/// are encoded into bytes using the specified charset. The charset can be specified by name or
/// defaults to the system's default charset.
class OutputStreamWriter final : public AbstractWriter {
 public:
  OutputStreamWriter(std::unique_ptr<AbstractWriter> outputStream, const std::string& charsetName) : output_writer_(std::move(outputStream)), charset_(charsetName), closed_(false) {
    if (charsetName != "UTF-8") {
      throw std::invalid_argument("Unsupported encoding: " + charsetName);
    }
  }

  explicit OutputStreamWriter(std::unique_ptr<AbstractWriter> outputStream) : OutputStreamWriter(std::move(outputStream), "UTF-8") {}

  ~OutputStreamWriter() override = default;

  /// @brief Get the encoding of the writer
  /// @return The encoding name as a string
  [[nodiscard]] auto getEncoding() const -> std::string { return closed_ ? "" : charset_; }

  /// @brief Write a single character
  /// @param c The character to write
  auto write(const char c) -> void override { write(std::string(1, c)); }

  /// @brief Write a portion of a character array
  /// @param cBuf The character array to write from
  /// @param off The offset in the array to start writing from
  /// @param len The number of characters to write
  auto write(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void override {
    if (closed_) {
      throw std::ios_base::failure("Stream is closed");
    }
    if (off + len > cBuf.size()) {
      throw std::out_of_range("Offset and length exceed buffer size");
    }
    output_writer_->write(cBuf, off, len);
    if (!output_writer_) {
      throw std::ios_base::failure("Failed to write to stream");
    }
  }

  /// @brief Write an entire character array
  /// @param cBuf The character array to write
  auto write(const std::vector<char>& cBuf) -> void override { write(cBuf, 0, cBuf.size()); }

  /// @brief Write a string
  /// @param str The string to write
  auto write(const std::string& str) -> void override { write(std::vector(str.begin(), str.end())); }

  /// @brief Write a portion of a string
  /// @param str The string to write from
  /// @param off The offset in the string to start writing from
  /// @param len The number of characters to write
  auto write(const std::string& str, const size_t off, const size_t len) -> void override {
    if (off + len > str.size()) {
      throw std::out_of_range("Offset and length exceed string size");
    }
    write(std::vector(str.begin() + static_cast<std::string::difference_type>(off), str.begin() + static_cast<std::string::difference_type>(off + len)));
  }

  /// @brief Flush the stream
  auto flush() -> void override {
    if (closed_) {
      throw std::ios_base::failure("Stream is closed");
    }
    output_writer_->flush();
    if (!output_writer_) {
      throw std::ios_base::failure("Failed to flush stream");
    }
  }

  /// @brief Close the writer
  auto close() -> void override {
    if (closed_) {
      return;
    }
    flush();
    closed_ = true;
  }

  /// @brief Append a character to the writer
  /// @param c The character to append
  /// @return A reference to this writer
  auto append(const char c) -> AbstractWriter& override {
    write(c);
    return *this;
  }

  /// @brief Append a string to the writer
  /// @param csq The string to append
  /// @return A reference to this writer
  auto append(const std::string& csq) -> AbstractWriter& override {
    write(csq);
    return *this;
  }

  /// @brief Append a subsequence of a string to the writer
  /// @param csq The string to append from
  /// @param start The starting index of the subsequence
  /// @param end The ending index of the subsequence
  /// @return A reference to this writer
  auto append(const std::string& csq, const size_t start, const size_t end) -> AbstractWriter& override {
    write(csq, start, end - start);
    return *this;
  }

  /// @brief Convert the writer to a string representation
  /// @return A string representation of the writer
  [[nodiscard]] auto toString() const -> std::string override {
    if (closed_) {
      throw std::ios_base::failure("Stream is closed");
    }
    return output_writer_->toString();
  }

 private:
  std::unique_ptr<AbstractWriter> output_writer_;
  std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> converter_;
  std::string charset_;
  bool closed_;
};
}  // namespace fox