#pragma once
#include <service/IConfigurable.hpp>
#include "GLogOptions.hpp"

namespace common {
  class GLogConfig final : public IConfigurable {
  public:
    GLogConfig();

  private:
    [[nodiscard]] auto doConfig() -> bool override;
    static auto configLogToStdout(const GLogOptions& glog_options) -> void;
    static auto clean() -> void;
  };
}
