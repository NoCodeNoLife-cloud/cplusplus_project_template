#pragma once
#include <memory>
#include <vector>

#include "FilterInputStream.hpp"

namespace common {
class BufferedInputStream final : public FilterInputStream {
 public:
  explicit BufferedInputStream(std::unique_ptr<AbstractInputStream> in);
  BufferedInputStream(std::unique_ptr<AbstractInputStream> in, int32_t size);
  [[nodiscard]] auto available() const -> size_t;
  auto close() -> void override;
  auto mark(int32_t readLimit) -> void override;
  [[nodiscard]] auto markSupported() const -> bool override;
  auto read() -> std::byte override;
  auto read(std::vector<std::byte>& buffer, size_t offset, size_t len)
      -> size_t override;
  auto reset() -> void override;
  auto skip(size_t n) -> size_t override;

 protected:
  static constexpr size_t DEFAULT_BUFFER_SIZE = 8192;
  std::vector<std::byte> buf_;
  size_t count_{0};
  size_t mark_limit_{0};
  size_t mark_pos_{0};
  size_t pos_{0};
  auto fillBuffer() -> void;
};
}  // namespace common
