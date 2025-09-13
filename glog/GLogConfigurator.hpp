#pragma once
#include <glog/logging.h>

#include <string>

#include "GLogParameters.hpp"
#include "filesystem/serialize/YamlObjectSerializer.hpp"
#include "service/interface/IConfigurable.hpp"
#include "service/interface/IStartupTask.hpp"

namespace service {
/// @brief Configurator class for Google Logging (glog) library.
/// This class handles the configuration and initialization of the glog logging system
/// by reading parameters from a YAML configuration file and setting up the appropriate
/// logging options.
class GLogConfigurator final : public IConfigurable, public IStartupTask {
 public:
  explicit GLogConfigurator(const std::string& GLogYAMLPath) {
    GLogYAMLPath_ = GLogYAMLPath;
    config_ = fox::YamlObjectSerializer<GLogParameters>::deserialize(GLogYAMLPath_);
  }

  /// @brief Execute the startup task.
  /// @return True if the task was executed successfully, false otherwise.
  bool execute() override {
    if (!doConfig()) {
      throw std::runtime_error("Configuration GLog failed");
    }
    return true;
  }

 private:
  std::string GLogYAMLPath_{};
  GLogParameters config_{};

  /// @brief Perform the configuration.
  /// @return True if the configuration was successful, false otherwise.
  [[nodiscard]] auto doConfig() -> bool override {
    google::InitGoogleLogging(config_.logName().c_str());
    FLAGS_minloglevel = config_.minLogLevel();
    configLogToStdout(config_);
    if (std::atexit(clean) != 0) {
      throw std::runtime_error("Failed to register cleanup function!");
    }
    LOG(INFO) << "configuring glog...";
    return true;
  }

  /// @brief Configure logging to stdout based on the provided options.
  /// @param glog_options The logging options to use for configuration.
  static auto configLogToStdout(const GLogParameters& glog_options) -> void { FLAGS_logtostderr = glog_options.logToStderr(); }

  /// @brief Clean up any resources used by the configurator.
  static auto clean() -> void { google::ShutdownGoogleLogging(); }
};
}  // namespace service