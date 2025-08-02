#include "AbstractFilterReader.hpp"

#include <stdexcept>

namespace common {
AbstractFilterReader::AbstractFilterReader(std::unique_ptr<AbstractReader> inputReader) {
  if (!reader_) {
    throw std::invalid_argument("Input reader cannot be null");
  }
  reader_ = std::move(inputReader);
}

AbstractFilterReader::~AbstractFilterReader() = default;

int32_t AbstractFilterReader::read() {
  if (!reader_) {
    throw std::runtime_error("Input stream is not available");
  }
  return reader_->read();
}

auto AbstractFilterReader::read(std::vector<char>& cBuf, const size_t off, const size_t len) -> size_t {
  if (!reader_) {
    throw std::runtime_error("Input stream is not available");
  }
  if (off + len > cBuf.size()) {
    return -1;
  }
  return reader_->read(cBuf, off, len);
}

size_t AbstractFilterReader::skip(const size_t n) {
  if (!reader_) {
    throw std::runtime_error("Input stream is not available");
  }
  return reader_->skip(n);
}

bool AbstractFilterReader::ready() const {
  if (!reader_) {
    throw std::runtime_error("Input stream is not available");
  }
  return reader_->ready();
}

bool AbstractFilterReader::markSupported() const {
  if (!reader_) {
    throw std::runtime_error("Input stream is not available");
  }
  return reader_->markSupported();
}

auto AbstractFilterReader::mark(const size_t readAheadLimit) -> void {
  if (!reader_) {
    throw std::runtime_error("Input stream is not available");
  }
  reader_->mark(readAheadLimit);
}

auto AbstractFilterReader::reset() -> void {
  if (!reader_) {
    throw std::runtime_error("Input stream is not available");
  }
  reader_->reset();
}

auto AbstractFilterReader::close() -> void {
  if (!reader_) {
    throw std::runtime_error("Input stream is not available");
  }
  reader_->close();
}
}  // namespace common
