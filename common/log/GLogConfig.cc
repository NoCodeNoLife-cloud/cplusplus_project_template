#include <filesystem/Directory.hpp>
#include <log/GLogConfig.hpp>

namespace common {
  GLogConfig::GLogConfig() {
    if (!doConfig()) {
      throw std::runtime_error("Failed to load config");
    }
  }

  auto GLogConfig::doConfig() -> bool {
    google::InitGoogleLogging(LOG_NAME.c_str());
    FLAGS_minloglevel = MIN_LOG_LEVEL;
    configLogToStdout();
    if (std::atexit(clean) != 0) {
      throw std::runtime_error("Failed to register cleanup function!");
    }
    return true;
  }

  auto GLogConfig::configLogToStdout() -> void {
    FLAGS_logtostderr = true;
  }

  auto GLogConfig::clean() -> void {
    google::ShutdownGoogleLogging();
  }
}
