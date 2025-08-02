#pragma once
#include <vector>

#include "filesystem/io/interface/ICloseable.hpp"
#include "filesystem/io/interface/IReadable.hpp"

namespace common {
class AbstractReader abstract : public ICloseable, public IReadable {
 public:
  ~AbstractReader() override;
  auto read() -> int32_t override;
  virtual auto read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t = 0;
  virtual auto read(std::vector<char>& cBuf) -> size_t;
  [[nodiscard]] virtual auto markSupported() const -> bool;
  virtual auto mark(size_t readAheadLimit) -> void = 0;
  virtual auto reset() -> void = 0;
  [[nodiscard]] virtual auto ready() const -> bool;
  virtual auto skip(size_t n) -> size_t;
};
}  // namespace common
