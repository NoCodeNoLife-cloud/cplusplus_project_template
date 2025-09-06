#include "PushbackReader.hpp"

#include <stdexcept>

namespace fox {
PushbackReader::PushbackReader(std::shared_ptr<AbstractReader> reader) : PushbackReader(std::move(reader), DEFAULT_BUFFER_SIZE) {}

PushbackReader::PushbackReader(std::shared_ptr<AbstractReader> reader, const size_t size) : FilterReader(std::move(reader)), buffer_(size) {
  if (size == 0) {
    throw std::invalid_argument("Buffer size must be greater than zero.");
  }
}

void PushbackReader::close() {
  FilterReader::close();
  buffer_.clear();
}

void PushbackReader::mark(size_t readAheadLimit) { throw std::runtime_error("mark() not supported."); }

bool PushbackReader::markSupported() const { return false; }

int32_t PushbackReader::read() {
  if (buffer_pos_ < buffer_.size()) {
    return buffer_[buffer_pos_++];
  }
  return FilterReader::read();
}

size_t PushbackReader::read(std::vector<char>& cBuf, size_t off, const size_t len) {
  if (off + len > cBuf.size()) {
    throw std::out_of_range("Buffer overflow.");
  }
  size_t bytesRead = 0;
  while (buffer_pos_ < buffer_.size() && bytesRead < len) {
    cBuf[off++] = buffer_[buffer_pos_++];
    bytesRead++;
  }
  if (bytesRead < len) {
    bytesRead += FilterReader::read(cBuf, off, len - bytesRead);
  }
  return bytesRead;
}

bool PushbackReader::ready() const { return buffer_pos_ < buffer_.size() || FilterReader::ready(); }

void PushbackReader::reset() { throw std::runtime_error("reset() not supported."); }

size_t PushbackReader::skip(size_t n) {
  size_t skipped = 0;
  if (buffer_pos_ < buffer_.size()) {
    const size_t bufferRemaining = buffer_.size() - buffer_pos_;
    skipped = std::min(n, bufferRemaining);
    buffer_pos_ += skipped;
    n -= skipped;
  }
  if (n > 0) {
    skipped += FilterReader::skip(n);
  }
  return skipped;
}

auto PushbackReader::unread(const std::vector<char>& cBuf) -> void { unread(cBuf, 0, cBuf.size()); }

auto PushbackReader::unread(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void {
  if (len > buffer_pos_) {
    throw std::overflow_error("Pushback buffer overflow.");
  }
  for (size_t i = 0; i < len; ++i) {
    buffer_[--buffer_pos_] = cBuf[off + len - 1 - i];
  }
}

auto PushbackReader::unread(const int32_t c) -> void {
  if (buffer_pos_ == 0) {
    throw std::overflow_error("Pushback buffer overflow.");
  }
  buffer_[--buffer_pos_] = static_cast<char>(c);
}
}  // namespace fox
