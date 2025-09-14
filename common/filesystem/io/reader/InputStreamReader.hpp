#pragma once
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING  // NOLINT(*-reserved-identifier)
#include <algorithm>
#include <codecvt>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "AbstractReader.hpp"

namespace fox {
/// @brief InputStreamReader is a class for reading characters from a byte stream.
/// This class inherits from AbstractReader and provides functionality to read characters
/// from an input stream with specified charset encoding.
class InputStreamReader final : public AbstractReader {
 public:
  explicit InputStreamReader(std::shared_ptr<AbstractReader> input);
  InputStreamReader(std::shared_ptr<AbstractReader> input, const std::string& charsetName);
  ~InputStreamReader() override;

  /// @brief Read a single character.
  /// @return The character read, as an integer in the range 0 to 65535 (0x00-0xffff),
  ///         or -1 if the end of the stream has been reached
  auto read() -> size_t override;

  /// @brief Read characters into an array.
  /// @param cBuf Destination buffer
  /// @param off Offset at which to start storing characters
  /// @param len Maximum number of characters to read
  /// @return The number of characters read, or -1 if the end of the stream has been reached
  auto read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t override;

  /// @brief Tests if this input stream is ready to be read.
  /// @return true if the next read() is guaranteed not to block for input, false otherwise.
  [[nodiscard]] auto ready() const -> bool override;

  /// @brief Close the stream.
  auto close() -> void override;

  /// @brief Tests if this stream supports the mark and reset methods.
  /// @return true if this stream type supports the mark and reset methods; false otherwise.
  [[nodiscard]] auto markSupported() const -> bool override;

  /// @brief Marks the current position in the stream.
  /// @param readAheadLimit the maximum limit of bytes that can be read before the mark position becomes invalid.
  auto mark(size_t readAheadLimit) -> void override;

  /// @brief Resets the stream to the most recent mark.
  auto reset() -> void override;

 private:
  std::shared_ptr<AbstractReader> reader_;
  std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter_;
};

inline InputStreamReader::InputStreamReader(std::shared_ptr<AbstractReader> input) : reader_(std::move(input)) {
  if (!reader_) {
    throw std::invalid_argument("Input stream cannot be null");
  }
}

inline InputStreamReader::InputStreamReader(std::shared_ptr<AbstractReader> input, const std::string& charsetName) : reader_(std::move(input)) {
  if (!reader_) {
    throw std::invalid_argument("Input stream cannot be null");
  }
  if (charsetName != "UTF-8") {
    throw std::invalid_argument("Only UTF-8 charset is supported in this implementation");
  }
}

inline InputStreamReader::~InputStreamReader() = default;

inline size_t InputStreamReader::read() {
  if (!reader_) {
    throw std::runtime_error("Input stream is not available");
  }

  std::vector<char> byteBuffer(4, 0);
  if (const size_t bytesRead = reader_->read(byteBuffer, 0, 1); bytesRead == 0 || bytesRead == static_cast<size_t>(-1)) {
    return static_cast<size_t>(-1);
  }

  try {
    const std::string byteStr(1, byteBuffer[0]);
    const char32_t charValue = converter_.from_bytes(byteStr)[0];
    return static_cast<size_t>(charValue);
  } catch (const std::exception&) {
    throw std::runtime_error("Failed to decode byte to character");
  }
}

inline auto InputStreamReader::read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t {
  if (!reader_) {
    throw std::runtime_error("Input stream is not available");
  }

  if (off > cBuf.size() || len > cBuf.size() - off) {
    throw std::out_of_range("Buffer overflow");
  }

  if (len == 0) {
    return 0;
  }

  std::vector<char> byteBuffer(len, 0);
  const size_t bytesRead = reader_->read(byteBuffer, 0, len);
  if (bytesRead == 0 || bytesRead == static_cast<size_t>(-1)) {
    return static_cast<size_t>(-1);
  }

  try {
    const std::string byteStr(byteBuffer.data(), bytesRead);
    auto chars = converter_.from_bytes(byteStr);
    const size_t charsToCopy = std::min(chars.size(), len);
    std::copy_n(chars.begin(), charsToCopy, cBuf.begin() + static_cast<std::vector<char>::difference_type>(off));
    return charsToCopy;
  } catch (const std::exception&) {
    throw std::runtime_error("Failed to decode bytes to characters");
  }
}

inline bool InputStreamReader::ready() const {
  if (!reader_) {
    throw std::runtime_error("Input stream is not available");
  }
  return reader_->ready();
}

inline auto InputStreamReader::close() -> void {
  if (!reader_) {
    throw std::runtime_error("Input stream is not available");
  }
  reader_->close();
}

inline bool InputStreamReader::markSupported() const { return false; }

inline auto InputStreamReader::mark(size_t readAheadLimit) -> void {
  static_cast<void>(readAheadLimit);  // Unused parameter
  throw std::runtime_error("Mark not supported");
}

inline auto InputStreamReader::reset() -> void { throw std::runtime_error("Reset not supported"); }
}  // namespace fox
