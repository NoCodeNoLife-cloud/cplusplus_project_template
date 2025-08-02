#include "FilterReader.hpp"

#include <stdexcept>

namespace common {
FilterReader::FilterReader(std::shared_ptr<AbstractReader> reader) : in_(std::move(reader)) {}

FilterReader::~FilterReader() = default;

auto FilterReader::close() -> void { in_->close(); }

auto FilterReader::mark(const size_t readAheadLimit) -> void { in_->mark(readAheadLimit); }

bool FilterReader::markSupported() const { return in_->markSupported(); }

int32_t FilterReader::read() { return in_->read(); }

auto FilterReader::read(std::vector<char>& cBuf, const size_t off, const size_t len) -> size_t {
  if (off + len > cBuf.size()) {
    throw std::out_of_range("Buffer overflow detected.");
  }
  return in_->read(cBuf, off, len);
}

size_t FilterReader::read(std::vector<char>& cBuf) { return in_->read(cBuf); }

bool FilterReader::ready() const { return in_->ready(); }

auto FilterReader::reset() -> void { in_->reset(); }

size_t FilterReader::skip(const size_t n) { return in_->skip(n); }
}  // namespace common
