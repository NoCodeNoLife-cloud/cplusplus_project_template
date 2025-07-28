#pragma once
#include <vector>

#include "AbstractInputStream.hpp"

namespace common {
class ByteArrayInputStream final : public AbstractInputStream {
 public:
  explicit ByteArrayInputStream(const std::vector<std::byte>& buf);
  auto read() -> std::byte override;
  auto skip(size_t n) -> size_t override;
  auto read(std::vector<std::byte>& cBuf, size_t off, size_t len)
      -> size_t override;
  size_t available() override;
  void reset() override;
  void mark(size_t readAheadLimit);
  [[nodiscard]] auto markSupported() const -> bool override;
  auto close() -> void override;

 protected:
  const std::vector<std::byte> buffer_;
  size_t pos_{0};
  size_t mark_position_{0};
};
}  // namespace common
