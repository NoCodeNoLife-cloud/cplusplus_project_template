#pragma once
#include <glog/logging.h>
#include <grpcpp/server_builder.h>
#include <yaml-cpp/node/node.h>

#include <string>

#include "GLogConfigurator.hpp"
#include "filesystem/serialize/YamlObjectSerializer.hpp"
#include "rpc/RpcServiceImpl.hpp"

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
  [[nodiscard]] auto maxConnectionIdleMs() const -> int32_t { return max_connection_idle_ms_; }
  [[nodiscard]] auto maxConnectionAgeMs() const -> int32_t { return max_connection_age_ms_; }
  [[nodiscard]] auto maxConnectionAgeGraceMs() const -> int32_t { return max_connection_age_grace_ms_; }
  [[nodiscard]] auto keepaliveTimeMs() const -> int32_t { return keepalive_time_ms_; }
  [[nodiscard]] auto keepaliveTimeoutMs() const -> int32_t { return keepalive_timeout_ms_; }
  [[nodiscard]] auto keepalivePermitWithoutCalls() const -> int32_t { return keepalive_permit_without_calls_; }

  // Setters
  auto maxConnectionIdleMs(const int32_t value) -> void { max_connection_idle_ms_ = value; }
  auto maxConnectionAgeMs(const int32_t value) -> void { max_connection_age_ms_ = value; }
  auto maxConnectionAgeGraceMs(const int32_t value) -> void { max_connection_age_grace_ms_ = value; }
  auto keepaliveTimeMs(const int32_t value) -> void { keepalive_time_ms_ = value; }
  auto keepaliveTimeoutMs(const int32_t value) -> void { keepalive_timeout_ms_ = value; }
  auto keepalivePermitWithoutCalls(const int32_t value) -> void { keepalive_permit_without_calls_ = value; }
};

/// @brief ServiceTask is responsible for managing the main service loop
/// and coordinating various subsystems within the application server.
class ServiceTask {
 public:
  /// @brief Initialize the service task and its associated resources
  /// @return true if initialization was successful
  auto init() -> void {
    LOG(INFO) << "Initializing ServiceTask with config path: " << config_path_;
    service::GLogConfigurator log_configurator{config_path_};
    log_configurator.execute();
    grpc_options_ = fox::YamlObjectSerializer<GrpcOptions>::deserialize(grpc_config_path_);
    LOG(INFO) << "ServiceTask starting...";
  }

  /// @brief Run the main task
  /// @return true if the task was successful
  auto run() -> void {
    try {
      init();
      establishGrpcConnection();
      exit();
    } catch (const std::exception& e) {
      LOG(ERROR) << "Exception occurred: " << e.what();
    } catch (...) {
      LOG(ERROR) << "Unknown exception occurred.";
    }
    LOG(INFO) << "ServiceTask completed.";
  }

  /// @brief Establish a gRPC connection to the specified service
  /// @return true if the connection was successfully established
  auto establishGrpcConnection() const -> void {
    LOG(INFO) << "Establishing gRPC connection...";
    try {
      // Build the server.
      const std::string server_address("0.0.0.0:50051");
      grpc::ServerBuilder builder;
      builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

      // Set the keepalive parameters.
      builder.AddChannelArgument(GRPC_ARG_MAX_CONNECTION_IDLE_MS, grpc_options_.maxConnectionIdleMs());
      builder.AddChannelArgument(GRPC_ARG_MAX_CONNECTION_AGE_MS, grpc_options_.maxConnectionAgeMs());
      builder.AddChannelArgument(GRPC_ARG_MAX_CONNECTION_AGE_GRACE_MS, grpc_options_.maxConnectionAgeGraceMs());
      builder.AddChannelArgument(GRPC_ARG_KEEPALIVE_TIME_MS, grpc_options_.keepaliveTimeMs());
      builder.AddChannelArgument(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, grpc_options_.keepaliveTimeoutMs());
      builder.AddChannelArgument(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, grpc_options_.keepalivePermitWithoutCalls());

      server_app::RpcServiceImpl service;
      builder.RegisterService(&service);

      const std::unique_ptr server(builder.BuildAndStart());
      LOG(INFO) << "Server listening on " << server_address;

      LOG(INFO) << "gRPC server started and waiting for connections...";
      server->Wait();
    } catch (...) {
      LOG(ERROR) << "gRPC server failed to start.";
    }
    LOG(INFO) << "gRPC connection established.";
  }

  /// @brief Exit the service task and clean up resources
  /// @return true if the task was successfully terminated
  static auto exit() -> void {
    LOG(INFO) << "Shutting down service task...";
    LOG(INFO) << "gRPC server shutdown complete.";
  }

 private:
  const std::string config_path_ = "../../app_server/config/glog.yaml";
  const std::string grpc_config_path_ = "../../app_server/config/grpc.yaml";
  GrpcOptions grpc_options_;
};
}  // namespace app_server

template <>
struct YAML::convert<app_server::GrpcOptions> {
  static auto decode(const Node& node, app_server::GrpcOptions& rhs) -> bool {
    rhs.maxConnectionIdleMs(node["maxConnectionIdleMs"].as<int32_t>());
    rhs.maxConnectionAgeMs(node["maxConnectionAgeMs"].as<int32_t>());
    rhs.maxConnectionAgeGraceMs(node["maxConnectionAgeGraceMs"].as<int32_t>());
    rhs.keepaliveTimeMs(node["keepaliveTimeMs"].as<int32_t>());
    rhs.keepaliveTimeoutMs(node["keepaliveTimeoutMs"].as<int32_t>());
    rhs.keepalivePermitWithoutCalls(node["keepalivePermitWithoutCalls"].as<int32_t>());
    return true;
  }
  static auto encode(const app_server::GrpcOptions& rhs) -> Node {
    Node node;
    node["maxConnectionIdleMs"] = rhs.maxConnectionIdleMs();
    node["maxConnectionAgeMs"] = rhs.maxConnectionAgeMs();
    node["maxConnectionAgeGraceMs"] = rhs.maxConnectionAgeGraceMs();
    node["keepaliveTimeMs"] = rhs.keepaliveTimeMs();
    node["keepaliveTimeoutMs"] = rhs.keepaliveTimeoutMs();
    node["keepalivePermitWithoutCalls"] = rhs.keepalivePermitWithoutCalls();
    return node;
  }
};