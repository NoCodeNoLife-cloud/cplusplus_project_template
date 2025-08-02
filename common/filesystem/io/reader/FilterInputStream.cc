#include "FilterInputStream.hpp"

#include <memory>
#include <stdexcept>

namespace common {
FilterInputStream::FilterInputStream(std::unique_ptr<AbstractInputStream> inputStream) : input_stream_(std::move(inputStream)) {}

FilterInputStream::~FilterInputStream() = default;

auto FilterInputStream::available() -> size_t {
  if (!input_stream_) {
    throw std::runtime_error("Input stream is not available");
  }
  return input_stream_->available();
}

void FilterInputStream::mark(const int32_t readLimit) {
  if (!input_stream_) {
    throw std::runtime_error("Input stream is not available");
  }
  input_stream_->mark(readLimit);
}

bool FilterInputStream::markSupported() const {
  if (!input_stream_) {
    return false;
  }
  return input_stream_->markSupported();
}

auto FilterInputStream::read() -> std::byte {
  if (!input_stream_) {
    throw std::runtime_error("Input stream is not available");
  }
  return input_stream_->read();
}

size_t FilterInputStream::read(std::vector<std::byte>& buffer) {
  if (!input_stream_) {
    throw std::runtime_error("Input stream is not available");
  }
  return input_stream_->read(buffer);
}

size_t FilterInputStream::read(std::vector<std::byte>& buffer, const size_t offset, const size_t len) {
  if (!input_stream_) {
    throw std::runtime_error("Input stream is not available");
  }
  return input_stream_->read(buffer, offset, len);
}

void FilterInputStream::reset() {
  if (!input_stream_) {
    throw std::runtime_error("Input stream is not available");
  }
  input_stream_->reset();
}

size_t FilterInputStream::skip(const size_t n) {
  if (!input_stream_) {
    throw std::runtime_error("Input stream is not available");
  }
  return input_stream_->skip(n);
}

auto FilterInputStream::close() -> void { input_stream_->close(); }
}  // namespace common
