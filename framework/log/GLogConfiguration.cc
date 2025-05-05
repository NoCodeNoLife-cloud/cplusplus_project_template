#include <filesystem/Directory.hpp>
#include <log/GLogConfiguration.hpp>

namespace framework::log {
  GLogConfiguration::GLogConfiguration() {
    config();
  }

  auto GLogConfiguration::config() const -> void {
    google::InitGoogleLogging(LOG_NAME.c_str());
    FLAGS_minloglevel = MIN_LOG_LEVEL;
    configLogToStdout();
    if (std::atexit(clean) != 0) {
      throw std::runtime_error("Failed to register cleanup function!");
    }
  }

  auto GLogConfiguration::configLogToStdout() -> void {
    FLAGS_logtostderr = true;
  }

  auto GLogConfiguration::clean() -> void {
    google::ShutdownGoogleLogging();
  }
} // namespace framework::log
