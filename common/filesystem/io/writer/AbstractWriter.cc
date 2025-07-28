#include "AbstractWriter.hpp"

namespace common {
AbstractWriter::AbstractWriter() = default;
AbstractWriter::~AbstractWriter() = default;

auto AbstractWriter::append(const char c) -> AbstractWriter& {
  write(c);
  return *this;
}

auto AbstractWriter::append(const std::string& csq) -> AbstractWriter& {
  write(csq);
  return *this;
}

auto AbstractWriter::append(const std::string& csq, const size_t start,
                            const size_t end) -> AbstractWriter& {
  write(csq, start, end);
  return *this;
}

auto AbstractWriter::write(const char c) -> void {
  const std::vector buf(1, c);
  write(buf, 0, 1);
}

auto AbstractWriter::write(const std::vector<char>& cBuf) -> void {
  write(cBuf, 0, cBuf.size());
}

auto AbstractWriter::write(const std::string& str) -> void {
  write(str, 0, str.size());
}

auto AbstractWriter::write(const std::string& str, const size_t off,
                           const size_t len) -> void {
  if (off < str.size()) {
    const size_t end = off + len < str.size() ? off + len : str.size();
    const std::vector buf(
        str.begin() + static_cast<std::string::difference_type>(off),
        str.begin() + static_cast<std::string::difference_type>(end));
    write(buf, 0, buf.size());
  }
}
}  // namespace common
