#include "ShortBuffer.hpp"

#include <stdexcept>

namespace common {
ShortBuffer::ShortBuffer(const size_t capacity) : buffer_(capacity) {
  capacity_ = capacity;
  limit_ = capacity;
  position_ = 0;
}

auto ShortBuffer::wrap(const int16_t* data, const size_t size) -> ShortBuffer {
  ShortBuffer sb(size);
  std::memcpy(sb.buffer_.data(), data, size * sizeof(int16_t));
  return sb;
}

auto ShortBuffer::get() -> int16_t {
  if (position_ >= limit_) {
    throw std::out_of_range("Position exceeds limit.");
  }
  return buffer_[position_++];
}

auto ShortBuffer::get(const size_t index) const -> int16_t {
  if (index >= limit_) {
    throw std::out_of_range("Index exceeds limit.");
  }
  return buffer_[index];
}

auto ShortBuffer::put(const int16_t value) -> void {
  if (position_ >= limit_) {
    throw std::out_of_range("Position exceeds limit.");
  }
  buffer_[position_++] = value;
}

auto ShortBuffer::put(const size_t index, const int16_t value) -> void {
  if (index >= limit_) {
    throw std::out_of_range("Index exceeds limit.");
  }
  buffer_[index] = value;
}

void ShortBuffer::rewind() { position_ = 0; }

auto ShortBuffer::data() -> int16_t* { return buffer_.data(); }

auto ShortBuffer::data() const -> const int16_t* { return buffer_.data(); }
}  // namespace common
