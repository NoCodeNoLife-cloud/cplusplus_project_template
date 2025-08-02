#include "PushbackInputStream.hpp"

#include <stdexcept>

namespace common {
PushbackInputStream::PushbackInputStream(std::unique_ptr<AbstractInputStream> inputStream, const size_t bufferSize) : FilterInputStream(std::move(inputStream)), pushback_buffer_(bufferSize), buffer_pos_(bufferSize) {}

PushbackInputStream::~PushbackInputStream() = default;

size_t PushbackInputStream::available() { return pushback_buffer_.size() - buffer_pos_ + input_stream_->available(); }

std::byte PushbackInputStream::read() {
  if (buffer_pos_ < pushback_buffer_.size()) {
    return pushback_buffer_[buffer_pos_++];
  }
  return input_stream_->read();
}

size_t PushbackInputStream::read(std::vector<std::byte>& buffer) { return read(buffer, 0, buffer.size()); }

size_t PushbackInputStream::read(std::vector<std::byte>& buffer, const size_t offset, const size_t len) {
  if (offset + len > buffer.size()) {
    throw std::out_of_range("Buffer overflow");
  }
  size_t bytesRead = 0;
  while (bytesRead < len && buffer_pos_ < pushback_buffer_.size()) {
    buffer[offset + bytesRead++] = pushback_buffer_[buffer_pos_++];
  }
  if (bytesRead < len) {
    bytesRead += input_stream_->read(buffer, offset + bytesRead, len - bytesRead);
  }
  return bytesRead;
}

void PushbackInputStream::unread(const std::vector<std::byte>& buffer) { unread(buffer, 0, buffer.size()); }

void PushbackInputStream::unread(const std::vector<std::byte>& buffer, const size_t offset, const size_t len) {
  if (len > buffer_pos_) {
    throw std::overflow_error("Pushback buffer overflow");
  }
  for (size_t i = 0; i < len; ++i) {
    pushback_buffer_[--buffer_pos_] = buffer[offset + len - i - 1];
  }
}

void PushbackInputStream::unread(const std::byte b) {
  if (buffer_pos_ == 0) {
    throw std::overflow_error("Pushback buffer overflow");
  }
  pushback_buffer_[--buffer_pos_] = b;
}
}  // namespace common
