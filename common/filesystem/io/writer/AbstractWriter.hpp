#pragma once
#include <vector>

#include "filesystem/io/interface/IAppendable.hpp"
#include "filesystem/io/interface/ICloseable.hpp"
#include "filesystem/io/interface/IFlushable.hpp"

namespace common {
class AbstractWriter : public ICloseable, public IFlushable, IAppendable<AbstractWriter> {
 public:
  AbstractWriter();
  ~AbstractWriter() override;
  auto append(char c) -> AbstractWriter& override;
  auto append(const std::string& csq) -> AbstractWriter& override;
  auto append(const std::string& csq, size_t start, size_t end) -> AbstractWriter& override;
  virtual auto write(char c) -> void;
  virtual auto write(const std::vector<char>& cBuf) -> void;
  virtual auto write(const std::vector<char>& cBuf, size_t off, size_t len) -> void = 0;
  virtual auto write(const std::string& str) -> void;
  virtual auto write(const std::string& str, size_t off, size_t len) -> void;
  [[nodiscard]] virtual auto toString() const -> std::string = 0;
};
}  // namespace common
