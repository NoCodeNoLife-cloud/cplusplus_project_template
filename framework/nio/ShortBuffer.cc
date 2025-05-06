#include <stdexcept>
#include <nio/ShortBuffer.hpp>

namespace framework {
  ShortBuffer::ShortBuffer(const size_t capacity) : buffer_(capacity) {
    capacity_ = capacity;
    limit_ = capacity;
    position_ = 0;
  }

  auto ShortBuffer::wrap(const short* data, const size_t size) -> ShortBuffer {
    ShortBuffer sb(size);
    std::memcpy(sb.buffer_.data(), data, size * sizeof(short));
    return sb;
  }

  auto ShortBuffer::get() -> short {
    if (position_ >= limit_) {
      throw std::out_of_range("Position exceeds limit.");
    }
    return buffer_[position_++];
  }

  auto ShortBuffer::get(const size_t index) const -> short {
    if (index >= limit_) {
      throw std::out_of_range("Index exceeds limit.");
    }
    return buffer_[index];
  }

  auto ShortBuffer::put(const short value) -> void {
    if (position_ >= limit_) {
      throw std::out_of_range("Position exceeds limit.");
    }
    buffer_[position_++] = value;
  }

  auto ShortBuffer::put(const size_t index, const short value) -> void {
    if (index >= limit_) {
      throw std::out_of_range("Index exceeds limit.");
    }
    buffer_[index] = value;
  }

  void ShortBuffer::rewind() {
    position_ = 0;
  }

  auto ShortBuffer::data() -> short* {
    return buffer_.data();
  }

  auto ShortBuffer::data() const -> const short* {
    return buffer_.data();
  }
}
