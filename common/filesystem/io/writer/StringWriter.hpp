#pragma once
#include <sstream>
#include <vector>

#include "AbstractWriter.hpp"

namespace common {
class StringWriter final : public AbstractWriter, public IAppendable<StringWriter> {
 public:
  explicit StringWriter(size_t initialSize);
  ~StringWriter() override;
  auto append(char c) -> StringWriter& override;
  auto append(const std::string& csq) -> StringWriter& override;
  auto append(const std::string& csq, size_t start, size_t end) -> StringWriter& override;
  auto close() -> void override;
  auto flush() -> void override;
  [[nodiscard]] auto getBuffer() const -> std::string;
  [[nodiscard]] auto toString() const -> std::string override;
  auto write(char c) -> void override;
  auto write(const std::string& str) -> void override;
  auto write(const std::string& str, size_t off, size_t len) -> void override;
  auto write(const std::vector<char>& cBuf, size_t off, size_t len) -> void override;

 private:
  std::ostringstream buffer_;
};
}  // namespace common
