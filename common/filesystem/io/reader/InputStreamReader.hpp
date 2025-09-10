#pragma once
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING  // NOLINT(*-reserved-identifier)
#include <codecvt>

#include "AbstractReader.hpp"

namespace fox {
/// @brief InputStreamReader is a class for reading characters from a byte stream.
/// This class inherits from AbstractReader and provides functionality to read characters
/// from an input stream with specified charset encoding.
class InputStreamReader final : public AbstractReader {
 public:
  explicit InputStreamReader(std::shared_ptr<AbstractReader> input) : reader_(std::move(input)) {
    if (!reader_) {
      throw std::invalid_argument("Input stream cannot be null");
    }
  }
  InputStreamReader(std::shared_ptr<AbstractReader> input, const std::string& charsetName) : reader_(std::move(input)) {
    if (!reader_) {
      throw std::invalid_argument("Input stream cannot be null");
    }
    if (charsetName != "UTF-8") {
      throw std::invalid_argument("Only UTF-8 charset is supported in this implementation");
    }
  }
  ~InputStreamReader() override = default;

  /// @brief Read a single character.
  /// @return The character read, as an integer in the range 0 to 65535
  auto read() -> int32_t override {
    if (!reader_) {
      throw std::runtime_error("Input stream is not available");
    }
    std::vector<char> byteBuffer(4, 0);
    if (const size_t bytesRead = reader_->read(byteBuffer, 0, 1); bytesRead == 0) {
      return -1;
    }
    try {
      const char32_t charValue = converter_.from_bytes(byteBuffer.data())[0];
      return static_cast<int32_t>(charValue);
    } catch (const std::exception&) {
      throw std::runtime_error("Failed to decode byte to character");
    }
  }

  /// @brief Read characters into an array.
  /// @param cBuf Destination buffer
  /// @param off Offset at which to start storing characters
  /// @param len Maximum number of characters to read
  /// @return The number of characters read, or -1 if the end of the stream has been reached
  auto read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t override {
    if (!reader_) {
      throw std::runtime_error("Input stream is not available");
    }
    if (off + len > cBuf.size()) {
      throw std::out_of_range("Buffer overflow");
    }
    std::vector<char> byteBuffer(len, 0);
    const size_t bytesRead = reader_->read(byteBuffer, 0, len);
    if (bytesRead == 0) {
      return -1;
    }
    try {
      auto chars = converter_.from_bytes(byteBuffer.data(), byteBuffer.data() + bytesRead);
      const size_t charsToCopy = std::min(chars.size(), len);
      std::copy_n(chars.begin(), charsToCopy, cBuf.begin() + static_cast<std::vector<char>::difference_type>(off));
      return charsToCopy;
    } catch (const std::exception&) {
      throw std::runtime_error("Failed to decode bytes to characters");
    }
  }

  /// @brief Reset the stream.
  [[nodiscard]] auto ready() const -> bool override {
    if (!reader_) {
      throw std::runtime_error("Input stream is not available");
    }
    return reader_->ready();
  }

  /// @brief Close the stream.
  auto close() -> void override {
    if (!reader_) {
      throw std::runtime_error("Input stream is not available");
    }
    reader_->close();
  }

  /// @brief Mark the current position in the stream.
  auto mark(size_t) -> void override { throw std::runtime_error("Mark not supported"); }

  /// @brief Reset the stream to the most recent mark.
  auto reset() -> void override { throw std::runtime_error("Reset not supported"); }

 private:
  std::shared_ptr<AbstractReader> reader_;
  std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter_;
};
}  // namespace fox
