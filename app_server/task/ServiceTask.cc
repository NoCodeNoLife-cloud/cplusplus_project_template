#include "ServiceTask.hpp"

#include <glog/logging.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server_builder.h>

#include "GLogConfigurator.hpp"
#include "generated/RpcService.grpc.pb.h"
#include "rpc/RpcServiceImpl.hpp"

namespace app_server {
auto GrpcOptions::maxConnectionIdleMs() const -> int32_t { return max_connection_idle_ms_; }
auto GrpcOptions::maxConnectionAgeMs() const -> int32_t { return max_connection_age_ms_; }
auto GrpcOptions::maxConnectionAgeGraceMs() const -> int32_t { return max_connection_age_grace_ms_; }
auto GrpcOptions::keepaliveTimeMs() const -> int32_t { return keepalive_time_ms_; }
auto GrpcOptions::keepaliveTimeoutMs() const -> int32_t { return keepalive_timeout_ms_; }
auto GrpcOptions::keepalivePermitWithoutCalls() const -> int32_t { return keepalive_permit_without_calls_; }
auto GrpcOptions::maxConnectionIdleMs(const int32_t value) -> void { max_connection_idle_ms_ = value; }
auto GrpcOptions::maxConnectionAgeMs(const int32_t value) -> void { max_connection_age_ms_ = value; }
auto GrpcOptions::maxConnectionAgeGraceMs(const int32_t value) -> void { max_connection_age_grace_ms_ = value; }
auto GrpcOptions::keepaliveTimeMs(const int32_t value) -> void { keepalive_time_ms_ = value; }
auto GrpcOptions::keepaliveTimeoutMs(const int32_t value) -> void { keepalive_timeout_ms_ = value; }
auto GrpcOptions::keepalivePermitWithoutCalls(const int32_t value) -> void { keepalive_permit_without_calls_ = value; }
auto ServiceTask::init() -> void {
  LOG(INFO) << "Initializing ServiceTask with config path: " << config_path_;
  service::GLogConfigurator log_configurator{config_path_};
  log_configurator.execute();
  grpc_options_ = fox::YamlObjectSerializer<GrpcOptions>::deserialize(grpc_config_path_);
  LOG(INFO) << "ServiceTask starting...";
}
auto ServiceTask::run() -> void {
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
auto ServiceTask::exit() -> void {
  LOG(INFO) << "Shutting down service task...";
  LOG(INFO) << "gRPC server shutdown complete.";
}
}  // namespace app_server
auto YAML::convert<app_server::GrpcOptions>::decode(const Node& node, app_server::GrpcOptions& rhs) -> bool {
  rhs.maxConnectionIdleMs(node["maxConnectionIdleMs"].as<int32_t>());
  rhs.maxConnectionAgeMs(node["maxConnectionAgeMs"].as<int32_t>());
  rhs.maxConnectionAgeGraceMs(node["maxConnectionAgeGraceMs"].as<int32_t>());
  rhs.keepaliveTimeMs(node["keepaliveTimeMs"].as<int32_t>());
  rhs.keepaliveTimeoutMs(node["keepaliveTimeoutMs"].as<int32_t>());
  rhs.keepalivePermitWithoutCalls(node["keepalivePermitWithoutCalls"].as<int32_t>());
  return true;
}
auto YAML::convert<app_server::GrpcOptions>::encode(const app_server::GrpcOptions& rhs) -> Node {
  Node node;
  node["maxConnectionIdleMs"] = rhs.maxConnectionIdleMs();
  node["maxConnectionAgeMs"] = rhs.maxConnectionAgeMs();
  node["maxConnectionAgeGraceMs"] = rhs.maxConnectionAgeGraceMs();
  node["keepaliveTimeMs"] = rhs.keepaliveTimeMs();
  node["keepaliveTimeoutMs"] = rhs.keepaliveTimeoutMs();
  node["keepalivePermitWithoutCalls"] = rhs.keepalivePermitWithoutCalls();
  return node;
}