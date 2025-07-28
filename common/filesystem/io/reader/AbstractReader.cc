#include "AbstractReader.hpp"

namespace common {
AbstractReader::~AbstractReader() = default;

auto AbstractReader::read() -> int32_t {
  std::vector<char> buffer(1);
  if (const size_t bytesRead = read(buffer, 0, 1); bytesRead == -1) {
    return -1;
  }
  return buffer[0];
}

auto AbstractReader::read(std::vector<char>& cBuf) -> size_t {
  return read(cBuf, 0, static_cast<int32_t>(cBuf.size()));
}

auto AbstractReader::markSupported() const -> bool { return false; }

auto AbstractReader::ready() const -> bool { return true; }

auto AbstractReader::skip(const size_t n) -> size_t {
  size_t skipped = 0;
  while (skipped < n) {
    std::vector<char> buffer(1024);
    const size_t toRead = std::min(n - skipped, buffer.size());
    const size_t readCount = read(buffer, 0, static_cast<int32_t>(toRead));
    if (readCount == -1) break;
    skipped += readCount;
  }
  return skipped;
}
}  // namespace common
