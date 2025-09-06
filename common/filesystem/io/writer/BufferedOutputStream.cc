#include "BufferedOutputStream.hpp"

namespace fox {
BufferedOutputStream::BufferedOutputStream(std::unique_ptr<AbstractOutputStream> out) : BufferedOutputStream(std::move(out), DEFAULT_BUFFER_SIZE) {}

BufferedOutputStream::BufferedOutputStream(std::unique_ptr<AbstractOutputStream> out, const size_t size) : FilterOutputStream(std::move(out)), bufferSize_(size), buffer_(size), buffer_position_(0) {
  if (!&output_stream_) {
    throw std::invalid_argument("Output stream cannot be null");
  }
  if (size == 0) {
    throw std::invalid_argument("Buffer size must be greater than 0");
  }
}

BufferedOutputStream::~BufferedOutputStream() {
  try {
    flush();
  } catch (...) {
  }
}

void BufferedOutputStream::write(const std::byte b) {
  if (buffer_position_ >= bufferSize_) {
    flushBuffer();
  }
  buffer_[buffer_position_++] = b;
}

void BufferedOutputStream::write(const std::vector<std::byte>& data, const size_t offset, const size_t len) {
  if (offset + len > data.size()) {
    throw std::out_of_range("Data offset/length out of range");
  }
  size_t bytesWritten = 0;
  while (bytesWritten < len) {
    if (buffer_position_ == bufferSize_) {
      flushBuffer();
    }
    const size_t bytesToCopy = std::min(len - bytesWritten, bufferSize_ - buffer_position_);
    std::memcpy(&buffer_[buffer_position_], &data[offset + bytesWritten], bytesToCopy);
    buffer_position_ += bytesToCopy;
    bytesWritten += bytesToCopy;
  }
}

void BufferedOutputStream::flush() {
  flushBuffer();
  output_stream_->flush();
}

void BufferedOutputStream::close() { output_stream_->close(); }

auto BufferedOutputStream::flushBuffer() -> void {
  if (buffer_position_ > 0) {
    output_stream_->write(buffer_, 0, buffer_position_);
    buffer_position_ = 0;
  }
}
}  // namespace fox
