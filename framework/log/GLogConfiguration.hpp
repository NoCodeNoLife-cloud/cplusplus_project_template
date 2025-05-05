#pragma once
#include <glog/logging.h>

namespace framework::log {
  class GLogConfiguration {
  public:
    GLogConfiguration();

  private:
    int32_t MIN_LOG_LEVEL{0};
    std::string LOG_NAME{"glog_main"};
    auto config() const -> void;
    static auto configLogToStdout() -> void;
    static auto clean() -> void;
  };
} // namespace framework::log
