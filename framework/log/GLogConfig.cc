#include <filesystem/Directory.hpp>
#include <log/GLogConfig.hpp>

namespace framework {
  GLogConfig::GLogConfig() {
    config();
  }

  auto GLogConfig::config() const -> void {
    google::InitGoogleLogging(LOG_NAME.c_str());
    FLAGS_minloglevel = MIN_LOG_LEVEL;
    configLogToStdout();
    if (std::atexit(clean) != 0) {
      throw std::runtime_error("Failed to register cleanup function!");
    }
  }

  auto GLogConfig::configLogToStdout() -> void {
    FLAGS_logtostderr = true;
  }

  auto GLogConfig::clean() -> void {
    google::ShutdownGoogleLogging();
  }
}
