#pragma once
// ReSharper disable once CppUnusedIncludeDirective
#include <grpcpp/grpcpp.h>

#include "utils/time/FunctionProfiler.hpp"

namespace app_client {
/// @brief A class that represents a client task
/// @details This class is responsible for running the main task and logging client info
class ClientTask {
  class RpcOptions {
    /// @brief Time interval between keepalive pings (in milliseconds)
    int keepalive_time_ms_ = 30 * 1000;
    /// @brief Timeout for keepalive ping acknowledgment (in milliseconds)
    int keepalive_timeout_ms_ = 5 * 1000;
    /// @brief Whether to permit keepalive pings when there are no active calls (1 = true, 0 = false)
    int keepalive_permit_without_calls_ = 1;

   public:
    // Getters
    [[nodiscard]] auto getKeepaliveTimeMs() const -> int;
    [[nodiscard]] auto getKeepaliveTimeoutMs() const -> int;
    [[nodiscard]] auto getKeepalivePermitWithoutCalls() const -> int;

    // Setters
    auto setKeepaliveTimeMs(int value) -> void;
    auto setKeepaliveTimeoutMs(int value) -> void;
    auto setKeepalivePermitWithoutCalls(int value) -> void;
  };

 public:
  explicit ClientTask(const std::string &project_name_) : timer_(project_name_) {}

  /// @brief Initialize the client task
  /// @return true if initialization was successful
  static auto init() -> void;

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
  common::FunctionProfiler timer_;
  RpcOptions rpc_options_;
};

}  // namespace app_client
