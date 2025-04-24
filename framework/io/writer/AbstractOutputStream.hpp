#pragma once
#include <format>
#include <vector>
#include "../interface/ICloseable.hpp"
#include "../interface/IFlushable.hpp"

namespace framework::io::writer {
  class AbstractOutputStream abstract : public iface::ICloseable, public iface::IFlushable {
  public:
    ~AbstractOutputStream() override;
    virtual auto write(std::byte b) -> void = 0;
    virtual auto write(const std::vector<std::byte>& buffer) -> void;
    virtual auto write(const std::vector<std::byte>& buffer, size_t offset, size_t len) -> void;
  };
} // namespace framework::io::writer
