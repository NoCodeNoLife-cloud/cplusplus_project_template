#include "ByteBuffer.hpp"

#include <stdexcept>

namespace common {
ByteBuffer::ByteBuffer(const size_t capacity) : buffer_(capacity) {
  capacity_ = capacity;
  limit_ = capacity;
}

void ByteBuffer::put(const std::vector<std::byte>& src) {
  if (src.size() > remaining()) {
    throw std::overflow_error("Insufficient space in buffer");
  }
  std::memcpy(buffer_.data() + position_, src.data(), src.size());
  position_ += src.size();
}

void ByteBuffer::put(const std::byte value) {
  if (!hasRemaining()) {
    throw std::overflow_error("Buffer overflow");
  }
  buffer_[position_++] = value;
}

auto ByteBuffer::get() -> std::byte {
  if (!hasRemaining()) {
    throw std::underflow_error("Buffer underflow");
  }
  return buffer_[position_++];
}

auto ByteBuffer::get(const size_t length) -> std::vector<std::byte> {
  if (length > remaining()) {
    throw std::underflow_error("Insufficient data in buffer");
  }
  std::vector result(buffer_.begin() + static_cast<std::ptrdiff_t>(position_), buffer_.begin() + static_cast<std::ptrdiff_t>(position_ + length));
  position_ += length;
  return result;
}
}  // namespace common
