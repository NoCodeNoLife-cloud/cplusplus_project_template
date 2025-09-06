#include "ByteArrayOutputStream.hpp"

namespace fox {
ByteArrayOutputStream::ByteArrayOutputStream() : buf_(32) {}

ByteArrayOutputStream::ByteArrayOutputStream(const size_t size) { buf_.resize(size); }

auto ByteArrayOutputStream::write(const std::byte b) -> void {
  if (count_ == buf_.size()) {
    buf_.resize(buf_.size() * 2);
  }
  buf_[count_++] = b;
}

void ByteArrayOutputStream::write(const std::vector<std::byte>& buffer, const size_t offset, const size_t len) {
  if (offset + len > buffer.size()) {
    throw std::out_of_range("Buffer offset/length out of range");
  }
  if (count_ + len > buf_.size()) {
    buf_.resize(std::max(buf_.size() * 2, count_ + len));
  }
  std::copy_n(buffer.begin() + static_cast<std::vector<char>::difference_type>(offset), len, buf_.begin() + static_cast<std::vector<char>::difference_type>(count_));
  count_ += len;
}

auto ByteArrayOutputStream::writeTo(AbstractOutputStream& out) const -> void { out.write(buf_, 0, count_); }

auto ByteArrayOutputStream::reset() -> void { count_ = 0; }

auto ByteArrayOutputStream::toByteArray() const -> std::vector<std::byte> { return {buf_.begin(), buf_.begin() + static_cast<std::vector<char>::difference_type>(count_)}; }

auto ByteArrayOutputStream::size() const -> size_t { return count_; }

auto ByteArrayOutputStream::toString() const -> std::string { return {reinterpret_cast<const char*>(buf_.data()), count_}; }

auto ByteArrayOutputStream::close() -> void {}

auto ByteArrayOutputStream::flush() -> void {
  // No operation for ByteArrayOutputStream.
}
}  // namespace fox
