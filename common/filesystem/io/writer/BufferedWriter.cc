#include "BufferedWriter.hpp"

#include <stdexcept>

namespace common {
BufferedWriter::BufferedWriter(std::unique_ptr<std::ofstream> os, const size_t size) : output_stream_(std::move(os)), buffer_size_(size) {
  if (!output_stream_->is_open()) {
    throw std::runtime_error("Output stream is not open.");
  }
  buffer_.reserve(size);
}

BufferedWriter::~BufferedWriter() { close(); }

void BufferedWriter::write(const std::string& str) {
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

auto BufferedWriter::write(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void {
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

auto BufferedWriter::newLine() -> BufferedWriter& {
  write("\n");
  return *this;
}

auto BufferedWriter::flush() -> void {
  if (!buffer_.empty()) {
    output_stream_->write(buffer_.data(), static_cast<std::streamsize>(buffer_.size()));
    buffer_.clear();
  }
}

auto BufferedWriter::close() -> void {
  flush();
  output_stream_->close();
}

BufferedWriter& BufferedWriter::append(const char c) {
  buffer_.push_back(static_cast<char>(c));
  if (buffer_.size() >= buffer_size_) {
    flush();
  }
  return *this;
}

BufferedWriter& BufferedWriter::append(const std::string& str) {
  for (const char c : str) {
    buffer_.push_back(static_cast<char>(c));
    if (buffer_.size() >= buffer_size_) {
      flush();
    }
  }
  return *this;
}

BufferedWriter& BufferedWriter::append(const std::string& str, const size_t start, const size_t end) {
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

auto BufferedWriter::toString() const -> std::string {
  std::string str;
  for (const char c : buffer_) {
    str.push_back(c);
  }
  return str;
}
}  // namespace common
