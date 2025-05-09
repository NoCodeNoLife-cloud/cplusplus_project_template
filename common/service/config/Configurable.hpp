#pragma once
#include <service/config/Config.hpp>

namespace common {
  class Configurable abstract {
  public:
    virtual ~Configurable();
    virtual bool configure(const Config& config) = 0;

  protected:
    virtual auto doConfigure(const Config& config) -> void = 0;
    [[nodiscard]] virtual auto validateConfig(const Config& config) const -> bool;
  };
}
