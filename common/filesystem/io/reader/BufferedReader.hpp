#pragma once
#include <fstream>

#include "AbstractReader.hpp"

namespace common {
class BufferedReader final : public AbstractReader {
 public:
  explicit BufferedReader(std::unique_ptr<AbstractReader> reader,
                          int32_t size = DEFAULT_BUFFER_SIZE);
  ~BufferedReader() override;
  auto close() -> void override;
  auto mark(size_t readAheadLimit) -> void override;
  [[nodiscard]] auto markSupported() const -> bool override;
  auto reset() -> void override;
  auto read() -> int32_t override;
  auto read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t override;
  auto readLine() -> std::string;
  [[nodiscard]] auto ready() const -> bool override;
  auto skip(int64_t n) -> int64_t;

 private:
  static constexpr size_t DEFAULT_BUFFER_SIZE = 8192;
  std::vector<char> buffer_;
  std::unique_ptr<AbstractReader> reader_;
  size_t buffer_size_{0};
  size_t pos_{0};
  size_t count_{0};
  size_t mark_limit_{0};
  bool fillBuffer();
};
}  // namespace common
