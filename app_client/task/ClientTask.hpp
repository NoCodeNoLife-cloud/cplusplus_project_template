#pragma once
// ReSharper disable once CppUnusedIncludeDirective
#include <grpcpp/grpcpp.h>
#include <yaml-cpp/node/node.h>

#include "utils/time/FunctionProfiler.hpp"

namespace app_client {
class GrpcOptions {
  /// @brief Time interval between keepalive pings (in milliseconds)
  int keepalive_time_ms_{30 * 1000};
  /// @brief Timeout for keepalive ping acknowledgment (in milliseconds)
  int keepalive_timeout_ms_{5 * 1000};
  /// @brief Whether to permit keepalive pings when there are no active calls (1 = true, 0 = false)
  int keepalive_permit_without_calls_{1};

 public:
  // Getters
  [[nodiscard]] auto keepaliveTimeMs() const -> int;
  [[nodiscard]] auto keepaliveTimeoutMs() const -> int;
  [[nodiscard]] auto keepalivePermitWithoutCalls() const -> int;

  // Setters
  auto keepaliveTimeMs(int value) -> void;
  auto keepaliveTimeoutMs(int value) -> void;
  auto keepalivePermitWithoutCalls(int value) -> void;
};

/// @brief A class that represents a client task
/// @details This class is responsible for running the main task and logging client info
class ClientTask {
 public:
  explicit ClientTask(const std::string& project_name_) : timer_(project_name_) {}

  /// @brief Initialize the client task
  /// @return true if initialization was successful
  auto init() -> void;

  /// @brief Run the main task
  /// @return true if the task was successful
  auto run() -> void;

  /// @brief Exit the client task
  /// @return true if exit was successful
  auto exit() -> void;

  /// @brief Logs client info
  static auto logClientInfo() -> void;

  /// @brief Create a gRPC channel with custom arguments
  /// @details This function sets up a gRPC channel with keepalive parameters and connects to the server
  /// @return A shared pointer to the created gRPC channel
  [[nodiscard]] auto createChannel() const -> std::shared_ptr<grpc::Channel>;

 private:
  const std::string config_path_ = "../../app_client/config/glog.yaml";
  const std::string rpc_config_path_ = "../../app_client/config/grpc.yaml";
  GrpcOptions rpc_options_;
  fox::FunctionProfiler timer_;
};
}  // namespace app_client

template <>
struct YAML::convert<app_client::GrpcOptions> {
  static auto decode(const Node& node, app_client::GrpcOptions& rhs) -> bool;
  static auto encode(const app_client::GrpcOptions& rhs) -> Node;
};