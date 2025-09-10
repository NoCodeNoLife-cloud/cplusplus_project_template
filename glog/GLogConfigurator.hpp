#pragma once
#include <glog/logging.h>

#include <string>

#include "filesystem/serialize/YamlObjectSerializer.hpp"
#include "service/interface/IConfigurable.hpp"
#include "service/interface/IStartupTask.hpp"

namespace service {
class GLogParameters final {
 public:
  /// @brief Get the minimum log level.
  /// @return The minimum log level as an integer.
  [[nodiscard]] auto minLogLevel() const -> int32_t { return min_log_level_; }

  /// @brief Get the log name.
  /// @return The log name as a string.
  [[nodiscard]] auto logName() const -> std::string { return log_name_; }

  /// @brief Check if logging to stderr is enabled.
  /// @return True if logging to stderr is enabled, false otherwise.
  [[nodiscard]] auto logToStderr() const -> bool { return log_to_stderr_; }

  /// @brief Set the minimum log level.
  /// @param min_log_level The minimum log level to set.
  auto minLogLevel(const int32_t min_log_level) -> void { min_log_level_ = min_log_level; }

  /// @brief Set the log name.
  /// @param log_name The log name to set.
  auto logName(const std::string& log_name) -> void { log_name_ = log_name; }

  /// @brief Enable or disable logging to stderr.
  /// @param log_to_stderr True to enable logging to stderr, false to disable.
  auto logToStderr(const bool log_to_stderr) -> void { log_to_stderr_ = log_to_stderr; }

 private:
  int32_t min_log_level_{};
  std::string log_name_{};
  bool log_to_stderr_{};
};

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

template <>
struct YAML::convert<service::GLogParameters> {
  static auto decode(const Node& node, service::GLogParameters& rhs) -> bool {
    rhs.minLogLevel(node["minLogLevel"].as<int32_t>());
    rhs.logName(node["logName"].as<std::string>());
    rhs.logToStderr(node["logToStderr"].as<bool>());
    return true;
  }

  static auto encode(const service::GLogParameters& rhs) -> Node {
    Node node;
    node["minLogLevel"] = rhs.minLogLevel();
    node["logName"] = rhs.logName();
    node["logToStderr"] = rhs.logToStderr();
    return node;
  }
};