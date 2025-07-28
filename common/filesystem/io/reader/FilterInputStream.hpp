#pragma once
#include <memory>

#include "AbstractInputStream.hpp"

namespace common {
class FilterInputStream : public AbstractInputStream {
 public:
  explicit FilterInputStream(std::unique_ptr<AbstractInputStream> inputStream);
  ~FilterInputStream() override;
  auto available() -> size_t override;
  auto mark(int32_t readLimit) -> void override;
  [[nodiscard]] auto markSupported() const -> bool override;
  auto read() -> std::byte override;
  size_t read(std::vector<std::byte>& buffer) override;
  size_t read(std::vector<std::byte>& buffer, size_t offset,
              size_t len) override;
  void reset() override;
  size_t skip(size_t n) override;
  auto close() -> void override;

 protected:
  std::unique_ptr<AbstractInputStream> input_stream_;
};
}  // namespace common
