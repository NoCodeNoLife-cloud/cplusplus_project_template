#include "ServiceTask.hpp"

#include <glog/logging.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server_builder.h>

#include "generated/RpcService.grpc.pb.h"
#include "log/GLogConfigurator.hpp"
#include "rpc/RpcServiceImpl.hpp"

namespace app_server {
auto ServiceTask::init() -> void {
  service::GLogConfigurator log_configurator;
  log_configurator.execute();
  LOG(INFO) << "ServiceTask starting...";
}

auto ServiceTask::run() const -> void {
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

auto ServiceTask::establishGrpcConnection() const -> void {
  LOG(INFO) << "Establishing gRPC connection...";
  try {
    // Build the server.
    const std::string server_address("0.0.0.0:50051");
    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

    // Set the keepalive parameters.
    builder.AddChannelArgument(GRPC_ARG_MAX_CONNECTION_IDLE_MS, max_connection_idle_ms_);
    builder.AddChannelArgument(GRPC_ARG_MAX_CONNECTION_AGE_MS, max_connection_age_ms_);
    builder.AddChannelArgument(GRPC_ARG_MAX_CONNECTION_AGE_GRACE_MS, max_connection_age_grace_ms_);
    builder.AddChannelArgument(GRPC_ARG_KEEPALIVE_TIME_MS, keepalive_time_ms_);
    builder.AddChannelArgument(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, keepalive_timeout_ms_);
    builder.AddChannelArgument(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, keepalive_permit_without_calls_);

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

auto ServiceTask::exit() -> void {
  LOG(INFO) << "Shutting down service task...";
  LOG(INFO) << "gRPC server shutdown complete.";
}
}  // namespace app_server