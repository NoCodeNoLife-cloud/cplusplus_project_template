#pragma once
#include <format>
#include <vector>

#include "filesystem/io/interface/ICloseable.hpp"
#include "filesystem/io/interface/IFlushable.hpp"

namespace common {
class AbstractOutputStream abstract : public ICloseable, public IFlushable {
 public:
  ~AbstractOutputStream() override;
  virtual auto write(std::byte b) -> void = 0;
  virtual auto write(const std::vector<std::byte>& buffer) -> void;
  virtual auto write(const std::vector<std::byte>& buffer, size_t offset,
                     size_t len) -> void;
};
}  // namespace common
