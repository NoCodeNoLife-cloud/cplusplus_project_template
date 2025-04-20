#include "GLogConfiguration.hpp"
#include <iostream>
#include "filesystem/File.hpp"
#include "time/Clock.hpp"

namespace framework::log {
  GLogConfiguration::GLogConfiguration() {
    config();
  }

  auto GLogConfiguration::config() const -> void {
    google::InitGoogleLogging(LOG_NAME.c_str());
    FLAGS_minloglevel = MIN_LOG_LEVEL;
    configLogToFile();
    configLogToStdout();
    if (std::atexit(clean) != 0) {
      throw std::runtime_error("Failed to register cleanup function!");
    }
  }

  auto GLogConfiguration::configLogToFile() const -> void {
    const std::string now_time = time::Clock::getCompressedCurrentDateTimeString();
    const std::string log_path = LOG_FILE_DIRECTORY + now_time + '/';
    if (const io::File file{log_path}; !file.exists() && !file.mkdir()) {
      throw std::runtime_error("Failed to create log file!");
    }
    google::SetLogDestination(google::GLOG_INFO, (log_path + "info_").c_str());
    google::SetLogDestination(google::GLOG_WARNING, (log_path + "warning_").c_str());
    google::SetLogDestination(google::GLOG_ERROR, (log_path + "error_").c_str());
    google::SetLogDestination(google::GLOG_FATAL, (log_path + "fatal_").c_str());
  }

  auto GLogConfiguration::configLogToStdout() const -> void {
    FLAGS_alsologtostderr = ALSO_LOG_TO_STDOUT;
    FLAGS_colorlogtostderr = COLOR_LOG_TO_STDOUT;
  }

  auto GLogConfiguration::clean() -> void {
    google::ShutdownGoogleLogging();
  }
} // namespace framework::log
