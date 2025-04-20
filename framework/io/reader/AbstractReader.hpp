#pragma once
#include <vector>

#include "../interface/ICloseable.hpp"
#include "../interface/IReadable.hpp"

namespace framework::io::reader {
  class AbstractReader abstract : public iface::ICloseable, public iface::IReadable {
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
} // namespace framework::io::reader
