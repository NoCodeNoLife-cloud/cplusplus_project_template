#pragma once
#include <glog/logging.h>
#include <grpcpp/server_builder.h>

#include <string>

#include "GLogConfigurator.hpp"
#include "GrpcOptions.hpp"
#include "filesystem/serialize/YamlObjectSerializer.hpp"
#include "rpc/RpcServiceImpl.hpp"

namespace app_server {
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