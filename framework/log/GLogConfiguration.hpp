#pragma once
#include <glog/logging.h>

namespace framework::log {

class GLogConfiguration {
 public:
  GLogConfiguration();
  GLogConfiguration(bool log_to_stdout, const std::string &log_name, bool color_log_to_stderr, int32_t min_log_level);

 private:
  bool log_to_stdout_{true};
  std::string LOG_NAME{"glog_main"};
  bool COLOR_LOG_TO_STDERR{true};
  int32_t MIN_LOG_LEVEL{0};

  auto config() const -> void;

  static auto clean() -> void;
};

}  // namespace framework::log
