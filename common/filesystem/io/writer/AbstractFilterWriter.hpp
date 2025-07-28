#pragma once
#include <memory>

#include "AbstractWriter.hpp"

namespace common {
class AbstractFilterWriter abstract : public AbstractWriter {
 public:
  explicit AbstractFilterWriter(std::unique_ptr<AbstractWriter> outputWriter);
  ~AbstractFilterWriter() override;
  auto write(char c) -> void override;
  auto write(const std::vector<char>& cBuf, size_t off, size_t len)
      -> void override;
  auto write(const std::vector<char>& cBuf) -> void override;
  auto write(const std::string& str, size_t off, size_t len) -> void override;
  auto write(const std::string& str) -> void override;
  auto flush() -> void override;
  auto close() -> void override;

 protected:
  std::unique_ptr<AbstractWriter> output_writer_;
};
}  // namespace common
