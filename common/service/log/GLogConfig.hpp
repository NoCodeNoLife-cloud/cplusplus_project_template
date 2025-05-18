#pragma once
#include <glog/logging.h>
#include <service/IConfigurable.hpp>

namespace common {
  class GLogConfig final : public IConfigurable {
  public:
    GLogConfig();

  private:
    int32_t MIN_LOG_LEVEL{0};
    std::string LOG_NAME{"glog_main"};
    [[nodiscard]] auto doConfig() -> bool override;
    static auto configLogToStdout() -> void;
    static auto clean() -> void;
  };
}
