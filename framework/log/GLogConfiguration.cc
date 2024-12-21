#include "GLogConfiguration.hpp"

#include <iostream>

namespace framework::log {

GLogConfiguration::GLogConfiguration() { config(); }

GLogConfiguration::GLogConfiguration(const bool log_to_stdout, const std::string& log_name, const bool color_log_to_stderr, const int32_t min_log_level) : log_to_stdout_(log_to_stdout), LOG_NAME(log_name), COLOR_LOG_TO_STDERR(color_log_to_stderr), MIN_LOG_LEVEL(min_log_level) { config(); }

auto GLogConfiguration::config() const -> void {
  google::InitGoogleLogging(LOG_NAME.c_str());
  FLAGS_logtostdout = log_to_stdout_;
  FLAGS_colorlogtostderr = COLOR_LOG_TO_STDERR;
  FLAGS_minloglevel = MIN_LOG_LEVEL;

  if (std::atexit(clean) != 0) {
    std::cerr << "Failed to register cleanup function!" << std::endl;
  }
}

auto GLogConfiguration::clean() -> void { google::ShutdownGoogleLogging(); }

}  // namespace framework::log