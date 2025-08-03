#pragma once
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#include <codecvt>

#include "AbstractWriter.hpp"

namespace common {
class OutputStreamWriter final : public AbstractWriter {
 public:
  OutputStreamWriter(std::unique_ptr<AbstractWriter> outputStream, const std::string& charsetName);
  explicit OutputStreamWriter(std::unique_ptr<AbstractWriter> outputStream);
  ~OutputStreamWriter() override;

  /// @brief Get the encoding of the writer
  /// @return The encoding name as a string
  [[nodiscard]] auto getEncoding() const -> std::string;

  /// @brief Write a single character
  /// @param c The character to write
  auto write(char c) -> void override;

  /// @brief Write a portion of a character array
  /// @param cBuf The character array to write from
  /// @param off The offset in the array to start writing from
  /// @param len The number of characters to write
  auto write(const std::vector<char>& cBuf, size_t off, size_t len) -> void override;

  /// @brief Write an entire character array
  /// @param cBuf The character array to write
  auto write(const std::vector<char>& cBuf) -> void override;

  /// @brief Write a string
  /// @param str The string to write
  auto write(const std::string& str) -> void override;

  /// @brief Write a portion of a string
  /// @param str The string to write from
  /// @param off The offset in the string to start writing from
  /// @param len The number of characters to write
  auto write(const std::string& str, size_t off, size_t len) -> void override;

  /// @brief Flush the stream
  auto flush() -> void override;

  /// @brief Close the writer
  auto close() -> void override;

  /// @brief Append a character to the writer
  /// @param c The character to append
  /// @return A reference to this writer
  auto append(char c) -> AbstractWriter& override;

  /// @brief Append a string to the writer
  /// @param csq The string to append
  /// @return A reference to this writer
  auto append(const std::string& csq) -> AbstractWriter& override;

  /// @brief Append a subsequence of a string to the writer
  /// @param csq The string to append from
  /// @param start The starting index of the subsequence
  /// @param end The ending index of the subsequence
  /// @return A reference to this writer
  auto append(const std::string& csq, size_t start, size_t end) -> AbstractWriter& override;

  /// @brief Convert the writer to a string representation
  /// @return A string representation of the writer
  [[nodiscard]] auto toString() const -> std::string override;

 private:
  std::unique_ptr<AbstractWriter> output_writer_;
  std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> converter_;
  std::string charset_;
  bool closed_;
};
}  // namespace common
