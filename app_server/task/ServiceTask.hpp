#pragma once
#include <yaml-cpp/node/node.h>

#include <string>

namespace app_server {
/// @brief A class that holds gRPC configuration options
class GrpcOptions {
  /// @brief Maximum time a connection can remain idle before being closed (in milliseconds)
  int32_t max_connection_idle_ms_{60 * 60 * 1000};
  /// @brief Maximum age of a connection before it is gracefully closed (in milliseconds)
  int32_t max_connection_age_ms_{2 * 60 * 60 * 1000};
  /// @brief Grace period after max connection age before force closing (in milliseconds)
  int32_t max_connection_age_grace_ms_{5 * 60 * 1000};
  /// @brief Time interval between keepalive pings (in milliseconds)
  int32_t keepalive_time_ms_{30 * 1000};
  /// @brief Timeout for keepalive ping acknowledgment (in milliseconds)
  int32_t keepalive_timeout_ms_{5 * 1000};
  /// @brief Whether to permit keepalive pings when there are no active calls (1 = true, 0 = false)
  int32_t keepalive_permit_without_calls_{1};

 public:
  // Getters
  [[nodiscard]] auto maxConnectionIdleMs() const -> int32_t;
  [[nodiscard]] auto maxConnectionAgeMs() const -> int32_t;
  [[nodiscard]] auto maxConnectionAgeGraceMs() const -> int32_t;
  [[nodiscard]] auto keepaliveTimeMs() const -> int32_t;
  [[nodiscard]] auto keepaliveTimeoutMs() const -> int32_t;
  [[nodiscard]] auto keepalivePermitWithoutCalls() const -> int32_t;

  // Setters
  auto maxConnectionIdleMs(int32_t value) -> void;
  auto maxConnectionAgeMs(int32_t value) -> void;
  auto maxConnectionAgeGraceMs(int32_t value) -> void;
  auto keepaliveTimeMs(int32_t value) -> void;
  auto keepaliveTimeoutMs(int32_t value) -> void;
  auto keepalivePermitWithoutCalls(int32_t value) -> void;
};

/// @brief ServiceTask is responsible for managing the main service loop
/// and coordinating various subsystems within the application server.
class ServiceTask {
 public:
  /// @brief Initialize the service task and its associated resources
  /// @return true if initialization was successful
  auto init() -> void;

  /// @brief Run the main task
  /// @return true if the task was successful
  auto run() -> void;

  /// @brief Establish a gRPC connection to the specified service
  /// @return true if the connection was successfully established
  auto establishGrpcConnection() const -> void;

  /// @brief Exit the service task and clean up resources
  /// @return true if the task was successfully terminated
  static auto exit() -> void;

 private:
  const std::string config_path_ = "../../app_server/config/glog.yaml";
  const std::string grpc_config_path_ = "../../app_server/config/grpc.yaml";
  GrpcOptions grpc_options_;
};
}  // namespace app_server

template <>
struct YAML::convert<app_server::GrpcOptions> {
  static auto decode(const Node& node, app_server::GrpcOptions& rhs) -> bool;
  static auto encode(const app_server::GrpcOptions& rhs) -> Node;
};