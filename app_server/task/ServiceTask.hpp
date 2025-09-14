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
    LOG(INFO) << "GLog configuration initialized successfully";

    LOG(INFO) << "Loading gRPC configuration from: " << grpc_config_path_;
    grpc_options_ = fox::YamlObjectSerializer<GrpcOptions>::deserialize(grpc_config_path_);
    LOG(INFO) << "gRPC configuration loaded successfully";
    LOG(INFO) << "gRPC Options - Max Connection Idle: " << grpc_options_.maxConnectionIdleMs()
              << "ms, Max Connection Age: " << grpc_options_.maxConnectionAgeMs()
              << "ms, Keepalive Time: " << grpc_options_.keepaliveTimeMs()
              << "ms, Keepalive Timeout: " << grpc_options_.keepaliveTimeoutMs()
              << "ms, Permit Without Calls: " << grpc_options_.keepalivePermitWithoutCalls();
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
      LOG(INFO) << "Configuring server to listen on: " << server_address;
      grpc::ServerBuilder builder;
      builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

      // Set the keepalive parameters.
      LOG(INFO) << "Setting gRPC server channel arguments";
      builder.AddChannelArgument(GRPC_ARG_MAX_CONNECTION_IDLE_MS, grpc_options_.maxConnectionIdleMs());
      builder.AddChannelArgument(GRPC_ARG_MAX_CONNECTION_AGE_MS, grpc_options_.maxConnectionAgeMs());
      builder.AddChannelArgument(GRPC_ARG_MAX_CONNECTION_AGE_GRACE_MS, grpc_options_.maxConnectionAgeGraceMs());
      builder.AddChannelArgument(GRPC_ARG_KEEPALIVE_TIME_MS, grpc_options_.keepaliveTimeMs());
      builder.AddChannelArgument(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, grpc_options_.keepaliveTimeoutMs());
      builder.AddChannelArgument(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, grpc_options_.keepalivePermitWithoutCalls());

      LOG(INFO) << "Channel arguments set - "
                << "Max Connection Idle: " << grpc_options_.maxConnectionIdleMs() << "ms, "
                << "Max Connection Age: " << grpc_options_.maxConnectionAgeMs() << "ms, "
                << "Max Connection Age Grace: " << grpc_options_.maxConnectionAgeGraceMs() << "ms, "
                << "Keepalive Time: " << grpc_options_.keepaliveTimeMs() << "ms, "
                << "Keepalive Timeout: " << grpc_options_.keepaliveTimeoutMs() << "ms, "
                << "Keepalive Permit Without Calls: " << grpc_options_.keepalivePermitWithoutCalls();

      server_app::RpcServiceImpl service;
      builder.RegisterService(&service);
      LOG(INFO) << "Service registered successfully";

      const std::unique_ptr server(builder.BuildAndStart());
      if (!server) {
        LOG(ERROR) << "Failed to build and start gRPC server";
        return;
      }

      LOG(INFO) << "Server listening on " << server_address;
      LOG(INFO) << "gRPC server started and waiting for connections...";
      server->Wait();
    } catch (const std::exception& e) {
      LOG(ERROR) << "gRPC server failed to start. Exception: " << e.what();
    } catch (...) {
      LOG(ERROR) << "gRPC server failed to start with unknown error.";
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