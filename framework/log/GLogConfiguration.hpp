#pragma once
#include <glog/logging.h>

namespace framework::log {
  class GLogConfiguration {
  public:
    GLogConfiguration();

  private:
    bool ALSO_LOG_TO_STDOUT{false};
    bool COLOR_LOG_TO_STDOUT{false};
    bool COLOR_LOG_TO_STDERR{true};
    int32_t MIN_LOG_LEVEL{0};
    std::string LOG_NAME{"glog_main"};
    std::string LOG_FILE_DIRECTORY{"../log/"};

    auto config() const -> void;
    auto configLogToFile() const -> void;
    auto configLogToStdout() const -> void;
    static auto clean() -> void;
  };
} // namespace framework::log
