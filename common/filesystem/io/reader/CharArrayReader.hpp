#pragma once
#include "AbstractReader.hpp"

namespace common {
class CharArrayReader final : public AbstractReader {
 public:
  explicit CharArrayReader(const std::vector<char>& buffer);
  CharArrayReader(const std::vector<char>& buffer, size_t offset,
                  size_t length);
  ~CharArrayReader() override;
  auto read() -> int32_t override;
  auto read(std::vector<char>& b, size_t off, size_t len) -> size_t override;
  auto skip(size_t n) -> size_t override;
  [[nodiscard]] auto ready() const -> bool override;
  [[nodiscard]] auto markSupported() const -> bool override;
  auto mark(size_t readAheadLimit) -> void override;
  auto reset() -> void override;
  auto close() -> void override;

 private:
  std::vector<char> buf_;
  size_t pos_{0};
  size_t marked_pos_{0};
  size_t count_{0};
};
}  // namespace common
