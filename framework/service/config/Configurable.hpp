#pragma once
#include "Config.hpp"

namespace framework::service::config {
  class Configurable abstract {
  public:
    virtual ~Configurable();

    virtual bool configure(const Config& config) = 0;

  protected:
    virtual auto doConfigure(const Config& config) -> void = 0;

    [[nodiscard]] virtual auto validateConfig(const Config& config) const -> bool;
  };
} // namespace framework::service::config
