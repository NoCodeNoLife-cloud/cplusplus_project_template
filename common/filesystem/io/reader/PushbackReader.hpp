#pragma once
#include "FilterReader.hpp"

namespace common {
class PushbackReader final : public FilterReader {
 public:
  explicit PushbackReader(std::shared_ptr<AbstractReader> reader);
  PushbackReader(std::shared_ptr<AbstractReader> reader, size_t size);
  auto close() -> void override;
  auto mark(size_t readAheadLimit) -> void override;
  [[nodiscard]] auto markSupported() const -> bool override;
  auto read() -> int32_t override;
  auto read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t override;
  [[nodiscard]] auto ready() const -> bool override;
  auto reset() -> void override;
  auto skip(size_t n) -> size_t override;
  auto unread(const std::vector<char>& cBuf) -> void;
  auto unread(const std::vector<char>& cBuf, size_t off, size_t len) -> void;
  auto unread(int32_t c) -> void;

 private:
  static constexpr size_t DEFAULT_BUFFER_SIZE = 1024;
  std::vector<char> buffer_;
  size_t buffer_pos_{DEFAULT_BUFFER_SIZE};
};
}  // namespace common
