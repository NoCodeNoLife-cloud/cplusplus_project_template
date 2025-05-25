#pragma once
#include <string>
#include <yaml-cpp/node/node.h>

namespace common {
  class GLogOptions final {
  public:
    GLogOptions();
    ~GLogOptions();
    GLogOptions(const GLogOptions& other);
    GLogOptions& operator=(const GLogOptions& other);
    GLogOptions(GLogOptions&& other) noexcept;
    [[nodiscard]] auto minLogLevel() const -> int32_t;
    [[nodiscard]] auto logName() const -> std::string;
    [[nodiscard]] auto logToStderr() const -> bool;
    auto minLogLevel(int32_t min_log_level) -> void;
    auto logName(const std::string& log_name) -> void;
    auto logToStderr(bool log_to_stderr) -> void;

  private:
    int32_t min_log_level_{};
    std::string log_name_;
    bool log_to_stderr_{};
  };
}

template <>
struct YAML::convert<common::GLogOptions> {
  static auto decode(const Node& node, common::GLogOptions& rhs) -> bool {
    rhs.minLogLevel(node["min_log_level"].as<int>());
    rhs.logName(node["log_name"].as<std::string>());
    rhs.logToStderr(node["log_to_stderr"].as<bool>());
    return true;
  }

  static auto encode(const common::GLogOptions& rhs) -> Node {
    Node node;
    node["min_log_level"] = rhs.minLogLevel();
    node["log_name"] = rhs.logName();
    node["log_to_stderr"] = rhs.logName();
    return node;
  }
};
