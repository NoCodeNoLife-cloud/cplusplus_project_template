#include "FilterReader.hpp"

#include <stdexcept>

namespace framework::io::reader {

FilterReader::FilterReader(std::shared_ptr<AbstractReader> reader) : in(std::move(reader)) {}

FilterReader::~FilterReader() = default;

auto FilterReader::close() -> void { in->close(); }

auto FilterReader::mark(const size_t readAheadLimit) -> void { in->mark(readAheadLimit); }

bool FilterReader::markSupported() const { return in->markSupported(); }

int32_t FilterReader::read() { return in->read(); }

auto FilterReader::read(std::vector<char>& cBuf, const size_t off, const size_t len) -> size_t {
  if (off + len > cBuf.size()) {
    throw std::out_of_range("Buffer overflow detected.");
  }
  return in->read(cBuf, off, len);
}

size_t FilterReader::read(std::vector<char>& cBuf) { return in->read(cBuf); }

bool FilterReader::ready() const { return in->ready(); }

auto FilterReader::reset() -> void { in->reset(); }

size_t FilterReader::skip(const size_t n) { return in->skip(n); }

}  // namespace framework::io::reader
