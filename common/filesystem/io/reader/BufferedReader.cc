#include "BufferedReader.hpp"

namespace common {
BufferedReader::BufferedReader(std::unique_ptr<AbstractReader> reader,
                               const int32_t size)
    : reader_(std::move(reader)), buffer_size_(size) {
  if (size <= 0) {
    throw std::invalid_argument("Buffer size must be greater than 0");
  }
  buffer_.resize(size);
}

BufferedReader::~BufferedReader() = default;

auto BufferedReader::close() -> void { reader_->close(); }

auto BufferedReader::mark(const size_t readAheadLimit) -> void {
  if (readAheadLimit <= 0) {
    throw std::invalid_argument("Mark limit must be greater than 0");
  }
  reader_->mark(readAheadLimit);
  mark_limit_ = readAheadLimit;
}

bool BufferedReader::markSupported() const { return true; }

auto BufferedReader::reset() -> void {
  reader_->reset();
  pos_ = mark_limit_;
}

int32_t BufferedReader::read() {
  if (pos_ >= count_) {
    if (!fillBuffer()) {
      return -1;
    }
  }
  return buffer_[pos_++];
}

auto BufferedReader::read(std::vector<char>& cBuf, size_t off, size_t len)
    -> size_t {
  if (off + len > cBuf.size()) {
    return -1;
  }
  size_t totalBytesRead = 0;
  if (len == 0) {
    return 0;
  }
  while (len > 0) {
    if (pos_ >= count_) {
      if (!fillBuffer()) {
        break;
      }
    }
    size_t bytesAvailable = count_ - pos_;
    const size_t bytesToRead = std::min(bytesAvailable, len);
    std::copy_n(buffer_.begin() + static_cast<std::ptrdiff_t>(pos_),
                bytesToRead, cBuf.begin() + static_cast<std::ptrdiff_t>(off));
    totalBytesRead += bytesToRead;
    off += bytesToRead;
    len -= bytesToRead;
    pos_ += bytesToRead;
  }
  return totalBytesRead;
}

auto BufferedReader::readLine() -> std::string {
  std::string line;
  while (true) {
    if (pos_ >= count_) {
      if (!fillBuffer()) {
        break;
      }
    }
    const char ch = buffer_[pos_++];
    if (ch == '\n') {
      break;
    }
    if (ch != '\r') {
      line += ch;
    }
  }
  return line;
}

bool BufferedReader::ready() const { return reader_->ready(); }

auto BufferedReader::skip(const int64_t n) -> int64_t {
  if (n <= 0) {
    throw std::invalid_argument("Skip value must be positive");
  }
  int64_t skipped = 0;
  while (skipped < n) {
    if (pos_ >= count_) {
      if (!fillBuffer()) {
        break;
      }
    }
    const int64_t bytesToSkip =
        std::min(static_cast<int64_t>(count_ - pos_), n - skipped);
    pos_ += bytesToSkip;
    skipped += bytesToSkip;
  }
  return skipped;
}

bool BufferedReader::fillBuffer() {
  pos_ = 0;
  count_ = reader_->read(buffer_, 0, buffer_size_);
  return count_ > 0;
}
}  // namespace common
