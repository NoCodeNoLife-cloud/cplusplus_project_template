#pragma once
#include <ostream>
#include <string>

#include "AbstractReader.hpp"

namespace common {
class StringReader final : public AbstractReader {
 public:
  explicit StringReader(std::string s);
  ~StringReader() override;
  auto close() -> void override;
  auto mark(size_t readAheadLimit) -> void override;
  [[nodiscard]] auto markSupported() const -> bool override;
  auto read() -> int32_t override;
  auto read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t override;
  [[nodiscard]] auto ready() const -> bool override;
  auto reset() -> void override;
  auto skip(size_t ns) -> size_t override;

 private:
  std::string source_;
  size_t position_;
  size_t mark_position_;
  bool mark_set_;
};
}  // namespace common
