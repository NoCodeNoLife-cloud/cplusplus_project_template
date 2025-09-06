#include "GLogConfigurator.hpp"

#include <glog/logging.h>

namespace service {
auto GLogParameters::minLogLevel() const -> int32_t { return min_log_level_; }
auto GLogParameters::logName() const -> std::string { return log_name_; }
auto GLogParameters::logToStderr() const -> bool { return log_to_stderr_; }
auto GLogParameters::minLogLevel(const int32_t min_log_level) -> void { min_log_level_ = min_log_level; }
auto GLogParameters::logName(const std::string& log_name) -> void { log_name_ = log_name; }
auto GLogParameters::logToStderr(const bool log_to_stderr) -> void { log_to_stderr_ = log_to_stderr; }
auto GLogConfigurator::execute() -> bool {
  if (!doConfig()) {
    throw std::runtime_error("Configuration GLog failed");
  }
  return true;
}
auto GLogConfigurator::doConfig() -> bool {
  google::InitGoogleLogging(config_.logName().c_str());
  FLAGS_minloglevel = config_.minLogLevel();
  configLogToStdout(config_);
  if (std::atexit(clean) != 0) {
    throw std::runtime_error("Failed to register cleanup function!");
  }
  LOG(INFO) << "configuring glog...";
  return true;
}
auto GLogConfigurator::configLogToStdout(const GLogParameters& glog_options) -> void { FLAGS_logtostderr = glog_options.logToStderr(); }
auto GLogConfigurator::clean() -> void { google::ShutdownGoogleLogging(); }
}  // namespace service
auto YAML::convert<service::GLogParameters>::decode(const Node& node, service::GLogParameters& rhs) -> bool {
  rhs.minLogLevel(node["minLogLevel"].as<int>());
  rhs.logName(node["logName"].as<std::string>());
  rhs.logToStderr(node["logToStderr"].as<bool>());
  return true;
}
auto YAML::convert<service::GLogParameters>::encode(const service::GLogParameters& rhs) -> Node {
  Node node;
  node["minLogLevel"] = rhs.minLogLevel();
  node["logName"] = rhs.logName();
  node["logToStderr"] = rhs.logToStderr();
  return node;
}
