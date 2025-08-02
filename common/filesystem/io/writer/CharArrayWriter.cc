#include "CharArrayWriter.hpp"

#include <stdexcept>

namespace common {
CharArrayWriter::CharArrayWriter() = default;

CharArrayWriter::CharArrayWriter(const int32_t initialSize) {
  if (initialSize < 0) {
    throw std::invalid_argument("initialSize must be non-negative");
  }
  buf_.reserve(initialSize);
}

CharArrayWriter::~CharArrayWriter() = default;

void CharArrayWriter::write(const char c) {
  if (count_ == buf_.size()) {
    buf_.push_back(c);
  } else {
    buf_[count_] = c;
  }
  ++count_;
}

auto CharArrayWriter::write(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void {
  if (off + len > static_cast<int32_t>(cBuf.size())) {
    throw std::out_of_range("Invalid offset or length");
  }
  if (count_ + len > static_cast<int32_t>(buf_.size())) {
    buf_.resize(count_ + len);
  }
  std::copy_n(cBuf.begin() + static_cast<std::ptrdiff_t>(off), len, buf_.begin() + static_cast<std::ptrdiff_t>(count_));
  count_ += len;
}

void CharArrayWriter::write(const std::string& str, const size_t off, const size_t len) {
  if (off + len > static_cast<int32_t>(str.size())) {
    throw std::out_of_range("Invalid offset or length");
  }
  if (count_ + len > static_cast<int32_t>(buf_.size())) {
    buf_.resize(count_ + len);
  }
  std::copy_n(str.begin() + static_cast<std::ptrdiff_t>(off), len, buf_.begin() + static_cast<std::ptrdiff_t>(count_));
  count_ += len;
}

auto CharArrayWriter::writeTo(AbstractWriter& out) const -> void { out.write(buf_, 0, count_); }

CharArrayWriter& CharArrayWriter::append(const std::string& csq) {
  write(csq, 0, csq.size());
  return *this;
}

CharArrayWriter& CharArrayWriter::append(const std::string& csq, const size_t start, const size_t end) {
  write(csq, start, end - start);
  return *this;
}

CharArrayWriter& CharArrayWriter::append(const char c) {
  write(c);
  return *this;
}

auto CharArrayWriter::reset() -> void { count_ = 0; }

auto CharArrayWriter::toCharArray() const -> std::vector<char> { return {buf_.begin(), buf_.begin() + static_cast<std::vector<char>::difference_type>(count_)}; }

auto CharArrayWriter::size() const -> size_t { return count_; }

auto CharArrayWriter::toString() const -> std::string { return {buf_.begin(), buf_.begin() + static_cast<std::vector<char>::difference_type>(count_)}; }

auto CharArrayWriter::flush() -> void {
  buf_.clear();
  count_ = 0;
}

auto CharArrayWriter::close() -> void {
  buf_.clear();
  count_ = 0;
}
}  // namespace common
