#pragma once
#include <memory>

namespace common {
  class ICloneable {
  public:
    virtual ~ICloneable() = default;
    [[nodiscard]] virtual auto clone() const -> std::unique_ptr<ICloneable> = 0;
  };
}
