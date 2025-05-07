#pragma once
#include <glog/logging.h>

namespace common {
  class GLogConfig {
  public:
    GLogConfig();

  private:
    int32_t MIN_LOG_LEVEL{0};
    std::string LOG_NAME{"glog_main"};
    auto config() const -> void;
    static auto configLogToStdout() -> void;
    static auto clean() -> void;
  };
}
