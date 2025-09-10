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
  explicit BufferedWriter(std::unique_ptr<std::ofstream> os, size_t size = DEFAULT_BUFFER_SIZE) : output_stream_(std::move(os)), buffer_size_(size) {
    if (!output_stream_->is_open()) {
      throw std::runtime_error("Output stream is not open.");
    }
    buffer_.reserve(size);
  }

  ~BufferedWriter() override { close(); }

  /// @brief Writes a string to the buffer.
  /// @param str The string to write.
  auto write(const std::string& str) -> void override {
    if (str.size() > buffer_size_) {
      flush();
      *output_stream_ << str;
    } else {
      for (const char c : str) {
        buffer_.push_back(static_cast<char>(c));
      }
      if (buffer_.size() >= buffer_size_) {
        flush();
      }
    }
  }

  /// @brief Writes a portion of a character buffer to the buffer.
  /// @param cBuf The character buffer to write from.
  /// @param off The offset in the buffer to start writing from.
  /// @param len The number of characters to write.
  auto write(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void override {
    if (off + len > cBuf.size()) {
      throw std::out_of_range("Offset and length are out of the bounds of the buffer.");
    }
    if (len > buffer_size_) {
      flush();
      output_stream_->write(cBuf.data() + off, static_cast<std::streamsize>(len));
    } else {
      for (size_t i = 0; i < len; ++i) {
        buffer_.push_back(cBuf[off + i]);
        if (buffer_.size() >= buffer_size_) {
          flush();
        }
      }
    }
  }

  /// @brief Writes a newline character to the buffer.
  /// @return A reference to this BufferedWriter instance.
  auto newLine() -> BufferedWriter& {
    write("\n");
    return *this;
  }

  /// @brief Flushes the buffer to the underlying output stream.
  auto flush() -> void override {
    if (!buffer_.empty()) {
      output_stream_->write(buffer_.data(), static_cast<std::streamsize>(buffer_.size()));
      buffer_.clear();
    }
  }

  /// @brief Closes the writer and releases any resources.
  auto close() -> void override {
    flush();
    output_stream_->close();
  }

  /// @brief Appends a single character to the buffer.
  /// @param c The character to append.
  /// @return A reference to this BufferedWriter instance.
  auto append(const char c) -> BufferedWriter& override {
    buffer_.push_back(static_cast<char>(c));
    if (buffer_.size() >= buffer_size_) {
      flush();
    }
    return *this;
  }

  /// @brief Appends a string to the buffer.
  /// @param str The string to append.
  /// @return A reference to this BufferedWriter instance.
  auto append(const std::string& str) -> BufferedWriter& override {
    for (const char c : str) {
      buffer_.push_back(static_cast<char>(c));
      if (buffer_.size() >= buffer_size_) {
        flush();
      }
    }
    return *this;
  }

  /// @brief Appends a substring to the buffer.
  /// @param str The string to append.
  /// @param start The starting index of the substring.
  /// @param end The ending index of the substring.
  /// @return A reference to this BufferedWriter instance.
  auto append(const std::string& str, const size_t start, const size_t end) -> BufferedWriter& override {
    if (start < str.length() && end <= str.length() && start < end) {
      for (size_t i = start; i < end; ++i) {
        buffer_.push_back(static_cast<char>(str[i]));
        if (buffer_.size() >= buffer_size_) {
          flush();
        }
      }
    }
    return *this;
  }

  /// @brief Converts the buffer content to a string representation.
  /// @return The string representation of the buffer content.
  [[nodiscard]] auto toString() const -> std::string override {
    std::string str;
    for (const char c : buffer_) {
      str.push_back(c);
    }
    return str;
  }

 private:
  static constexpr size_t DEFAULT_BUFFER_SIZE = 1024;
  std::unique_ptr<std::ofstream> output_stream_;
  std::vector<char> buffer_;
  size_t buffer_size_;
};
}  // namespace fox