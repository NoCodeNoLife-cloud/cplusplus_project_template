#include "CharBuffer.hpp"

#include <algorithm>
#include <span>
#include <stdexcept>

namespace common {
CharBuffer::CharBuffer(const size_t cap) : buffer_(cap, u'\0') {
  position_ = 0;
  limit_ = cap;
  capacity_ = cap;
}

auto CharBuffer::compact() -> void {
  if (position_ > 0) {
    std::move(buffer_.begin() + static_cast<std::ptrdiff_t>(position_), buffer_.begin() + static_cast<std::ptrdiff_t>(limit_), buffer_.begin());
    limit_ -= position_;
    position_ = 0;
  }
}

auto CharBuffer::put(const char c) -> void {
  if (position_ >= limit_) {
    throw std::overflow_error("Buffer overflow.");
  }
  buffer_[position_++] = c;
}

auto CharBuffer::put(const std::u16string& src) -> void {
  if (position_ + src.size() > limit_) {
    throw std::overflow_error("Buffer overflow.");
  }
  std::ranges::copy(src, buffer_.begin() + static_cast<std::ptrdiff_t>(position_));
  position_ += src.size();
}

auto CharBuffer::get() -> char16_t {
  if (position_ >= limit_) {
    throw std::underflow_error("Buffer underflow.");
  }
  return buffer_[position_++];
}

auto CharBuffer::getRemaining() const -> std::string { return {buffer_.begin() + static_cast<std::ptrdiff_t>(position_), buffer_.begin() + static_cast<std::ptrdiff_t>(limit_)}; }
}  // namespace common
