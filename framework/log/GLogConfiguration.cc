#include "GLogConfiguration.hpp"

#include <iostream>
#include <utility>

namespace framework::log {

GLogConfiguration::GLogConfiguration() { config(); }

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
  google::SetLogDestination(google::GLOG_INFO, (LOG_FILE_DIRECTORY + "info_").c_str());
  google::SetLogDestination(google::GLOG_WARNING, (LOG_FILE_DIRECTORY + "warning_").c_str());
  google::SetLogDestination(google::GLOG_ERROR, (LOG_FILE_DIRECTORY + "error_").c_str());
  google::SetLogDestination(google::GLOG_FATAL, (LOG_FILE_DIRECTORY + "fatal_").c_str());
}

auto GLogConfiguration::configLogToStdout() const -> void {
  FLAGS_alsologtostderr = ALSO_LOG_TO_STDOUT;
  FLAGS_colorlogtostderr = COLOR_LOG_TO_STDOUT;
}

auto GLogConfiguration::clean() -> void { google::ShutdownGoogleLogging(); }

}  // namespace framework::log