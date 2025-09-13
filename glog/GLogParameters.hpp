#pragma once
#include <yaml-cpp/node/node.h>

#include <string>

namespace service {
/// @brief Configuration parameters for Google Logging (glog) library.
/// This class encapsulates all the configuration options for the glog logging system.
/// It provides getter and setter methods for each parameter and supports YAML serialization.
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
}  // namespace service

/// @brief YAML serialization specialization for GLogParameters.
/// Provides methods to encode and decode GLogParameters to/from YAML nodes.
template <>
struct YAML::convert<service::GLogParameters> {
  /// @brief Decode a YAML node into a GLogParameters object.
  /// @param node The YAML node containing the configuration data.
  /// @param rhs The GLogParameters object to populate.
  /// @return True if decoding was successful.
  static auto decode(const Node& node, service::GLogParameters& rhs) -> bool {
    rhs.minLogLevel(node["minLogLevel"].as<int32_t>());
    rhs.logName(node["logName"].as<std::string>());
    rhs.logToStderr(node["logToStderr"].as<bool>());
    return true;
  }

  /// @brief Encode a GLogParameters object into a YAML node.
  /// @param rhs The GLogParameters object to encode.
  /// @return A YAML node containing the configuration data.
  static auto encode(const service::GLogParameters& rhs) -> Node {
    Node node;
    node["minLogLevel"] = rhs.minLogLevel();
    node["logName"] = rhs.logName();
    node["logToStderr"] = rhs.logToStderr();
    return node;
  }
};