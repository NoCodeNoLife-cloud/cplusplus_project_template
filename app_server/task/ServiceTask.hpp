#pragma once

namespace app_server {
/// @brief A class that holds gRPC configuration options
class GrpcOptions {
  /// @brief Maximum time a connection can remain idle before being closed (in milliseconds)
  int max_connection_idle_ms_ = 60 * 60 * 1000;
  /// @brief Maximum age of a connection before it is gracefully closed (in milliseconds)
  int max_connection_age_ms_ = 2 * 60 * 60 * 1000;
  /// @brief Grace period after max connection age before force closing (in milliseconds)
  int max_connection_age_grace_ms_ = 5 * 60 * 1000;
  /// @brief Time interval between keepalive pings (in milliseconds)
  int keepalive_time_ms_ = 30 * 1000;
  /// @brief Timeout for keepalive ping acknowledgment (in milliseconds)
  int keepalive_timeout_ms_ = 5 * 1000;
  /// @brief Whether to permit keepalive pings when there are no active calls (1 = true, 0 = false)
  int keepalive_permit_without_calls_ = 1;

 public:
  // Getters
  [[nodiscard]] auto getMaxConnectionIdleMs() const -> int;
  [[nodiscard]] auto getMaxConnectionAgeMs() const -> int;
  [[nodiscard]] auto getMaxConnectionAgeGraceMs() const -> int;
  [[nodiscard]] auto getKeepaliveTimeMs() const -> int;
  [[nodiscard]] auto getKeepaliveTimeoutMs() const -> int;
  [[nodiscard]] auto getKeepalivePermitWithoutCalls() const -> int;

  // Setters
  auto setMaxConnectionIdleMs(int value) -> void;
  auto setMaxConnectionAgeMs(int value) -> void;
  auto setMaxConnectionAgeGraceMs(int value) -> void;
  auto setKeepaliveTimeMs(int value) -> void;
  auto setKeepaliveTimeoutMs(int value) -> void;
  auto setKeepalivePermitWithoutCalls(int value) -> void;
};

/// @brief ServiceTask is responsible for managing the main service loop
/// and coordinating various subsystems within the application server.
class ServiceTask {
 public:
  /// @brief Initialize the service task and its associated resources
  /// @return true if initialization was successful
  static auto init() -> void;

  /// @brief Run the main task
  /// @return true if the task was successful
  auto run() const -> void;

  /// @brief Establish a gRPC connection to the specified service
  /// @return true if the connection was successfully established
  auto establishGrpcConnection() const -> void;

  /// @brief Exit the service task and clean up resources
  /// @return true if the task was successfully terminated
  static auto exit() -> void;

 private:
  GrpcOptions grpc_options_;
};
}  // namespace app_server