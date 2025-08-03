#pragma once
#include <string>

namespace service {
class ConfigPath {
 public:
  /// @brief Get the full path of the configuration file by name
  /// @param config_name The name of the configuration file
  /// @return The full path of the configuration file
  [[nodiscard]] static auto getConfigPath(const std::string& config_name) -> std::string;

 private:
  static inline std::string CONFIG_DIR = "../../common_service/config/";
};
}  // namespace service
