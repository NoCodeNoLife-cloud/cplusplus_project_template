#include "OutputStreamWriter.hpp"

namespace common {
OutputStreamWriter::OutputStreamWriter(
    std::unique_ptr<AbstractWriter> outputStream,
    const std::string& charsetName)
    : output_writer_(std::move(outputStream)),
      charset_(charsetName),
      closed_(false) {
  if (charsetName != "UTF-8") {
    throw std::invalid_argument("Unsupported encoding: " + charsetName);
  }
}

OutputStreamWriter::OutputStreamWriter(
    std::unique_ptr<AbstractWriter> outputStream)
    : OutputStreamWriter(std::move(outputStream), "UTF-8") {}

OutputStreamWriter::~OutputStreamWriter() = default;

auto OutputStreamWriter::getEncoding() const -> std::string {
  return closed_ ? "" : charset_;
}

void OutputStreamWriter::write(const char c) { write(std::string(1, c)); }

auto OutputStreamWriter::write(const std::vector<char>& cBuf, const size_t off,
                               const size_t len) -> void {
  if (closed_) {
    throw std::ios_base::failure("Stream is closed");
  }
  if (off + len > cBuf.size()) {
    throw std::out_of_range("Offset and length exceed buffer size");
  }
  output_writer_->write(cBuf, off, len);
  if (!output_writer_) {
    throw std::ios_base::failure("Failed to write to stream");
  }
}

void OutputStreamWriter::write(const std::vector<char>& cBuf) {
  write(cBuf, 0, cBuf.size());
}

void OutputStreamWriter::write(const std::string& str) {
  write(std::vector(str.begin(), str.end()));
}

void OutputStreamWriter::write(const std::string& str, const size_t off,
                               const size_t len) {
  if (off + len > str.size()) {
    throw std::out_of_range("Offset and length exceed string size");
  }
  write(std::vector(
      str.begin() + static_cast<std::string::difference_type>(off),
      str.begin() + static_cast<std::string::difference_type>(off + len)));
}

auto OutputStreamWriter::flush() -> void {
  if (closed_) {
    throw std::ios_base::failure("Stream is closed");
  }
  output_writer_->flush();
  if (!output_writer_) {
    throw std::ios_base::failure("Failed to flush stream");
  }
}

auto OutputStreamWriter::close() -> void {
  if (closed_) {
    return;
  }
  flush();
  closed_ = true;
}

AbstractWriter& OutputStreamWriter::append(const char c) {
  write(c);
  return *this;
}

AbstractWriter& OutputStreamWriter::append(const std::string& csq) {
  write(csq);
  return *this;
}

AbstractWriter& OutputStreamWriter::append(const std::string& csq,
                                           const size_t start,
                                           const size_t end) {
  write(csq, start, end - start);
  return *this;
}

auto OutputStreamWriter::toString() const -> std::string {
  if (closed_) {
    throw std::ios_base::failure("Stream is closed");
  }
  return output_writer_->toString();
}
}  // namespace common
