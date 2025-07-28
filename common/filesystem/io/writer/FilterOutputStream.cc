#include "FilterOutputStream.hpp"

namespace common {
FilterOutputStream::FilterOutputStream(
    std::shared_ptr<AbstractOutputStream> outputStream)
    : output_stream_(std::move(outputStream)) {}

FilterOutputStream::~FilterOutputStream() = default;

auto FilterOutputStream::write(const std::byte b) -> void {
  if (!output_stream_) {
    throw std::runtime_error("Output stream is not available");
  }
  output_stream_->write(b);
}

void FilterOutputStream::write(const std::vector<std::byte>& buffer) {
  if (!output_stream_) {
    throw std::runtime_error("Output stream is not available");
  }
  output_stream_->write(buffer);
}

void FilterOutputStream::write(const std::vector<std::byte>& buffer,
                               const size_t offset, const size_t len) {
  if (!output_stream_) {
    throw std::runtime_error("Output stream is not available");
  }
  if (offset + len > buffer.size()) {
    throw std::out_of_range("Buffer overflow");
  }
  output_stream_->write(buffer, offset, len);
}

auto FilterOutputStream::flush() -> void {
  if (!output_stream_) {
    throw std::runtime_error("Output stream is not available");
  }
  output_stream_->flush();
}

auto FilterOutputStream::close() -> void {
  if (!output_stream_) {
    throw std::runtime_error("Output stream is not available");
  }
  flush();
  output_stream_->close();
}
}  // namespace common
