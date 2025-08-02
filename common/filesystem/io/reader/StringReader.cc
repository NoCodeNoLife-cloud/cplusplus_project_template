#include "StringReader.hpp"

#include <utility>

namespace common {
StringReader::StringReader(std::string s) : source_(std::move(s)), position_(0), mark_position_(0), mark_set_(false) {}

StringReader::~StringReader() = default;

auto StringReader::close() -> void {
  source_.clear();
  position_ = 0;
  mark_position_ = 0;
  mark_set_ = false;
}

auto StringReader::mark(const size_t readAheadLimit) -> void {
  mark_position_ = readAheadLimit;
  mark_set_ = true;
}

bool StringReader::markSupported() const { return true; }

int32_t StringReader::read() {
  if (position_ >= source_.size()) {
    return -1;  // EOF
  }
  return source_[position_++];
}

auto StringReader::read(std::vector<char>& cBuf, const size_t off, const size_t len) -> size_t {
  if (off >= cBuf.size()) {
    throw std::invalid_argument("Offset is out of bounds of the buffer");
  }
  const size_t maxRead = std::min(len, source_.size() - position_);
  const size_t actualRead = std::min(maxRead, cBuf.size() - off);
  for (size_t i = 0; i < actualRead; ++i) {
    if (position_ < source_.size()) {
      cBuf[off + i] = source_[position_++];
    } else {
      break;
    }
  }
  return actualRead;
}

bool StringReader::ready() const { return position_ < source_.size(); }

auto StringReader::reset() -> void {
  if (!mark_set_) {
    position_ = 0;
  } else {
    position_ = mark_position_;
  }
}

size_t StringReader::skip(const size_t ns) {
  const size_t charsToSkip = std::min(ns, source_.size() - position_);
  position_ += charsToSkip;
  return static_cast<int64_t>(charsToSkip);
}
}  // namespace common
