#include <glog/logging.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/support/channel_arguments.h>

#include <rpc/RpcClient.hpp>
#include <task/ClientTask.hpp>

#include "../../glog/GLogConfigurator.hpp"
#include "utils/system/SystemInfo.hpp"

namespace app_client {
auto GrpcOptions::keepaliveTimeMs() const -> int { return keepalive_time_ms_; }
auto GrpcOptions::keepaliveTimeoutMs() const -> int { return keepalive_timeout_ms_; }
auto GrpcOptions::keepalivePermitWithoutCalls() const -> int { return keepalive_permit_without_calls_; }
auto GrpcOptions::keepaliveTimeMs(const int value) -> void { keepalive_time_ms_ = value; }
auto GrpcOptions::keepaliveTimeoutMs(const int value) -> void { keepalive_timeout_ms_ = value; }
auto GrpcOptions::keepalivePermitWithoutCalls(const int value) -> void { keepalive_permit_without_calls_ = value; }
auto ClientTask::init() -> void {
  LOG(INFO) << "Initializing GLog configuration from: " << config_path_;
  service::GLogConfigurator log_configurator{config_path_};
  log_configurator.execute();

  LOG(INFO) << "Loading RPC configuration from: " << rpc_config_path_;
  rpc_options_ = fox::YamlObjectSerializer<GrpcOptions>::deserialize(rpc_config_path_);

  LOG(INFO) << "Application starting...";
  logClientInfo();
  LOG(INFO) << "Initialization completed successfully";
}
auto ClientTask::createChannel() const -> std::shared_ptr<grpc::Channel> {
  // Setup channel.
  grpc::ChannelArguments channel_args;
  channel_args.SetInt(GRPC_ARG_KEEPALIVE_TIME_MS, rpc_options_.keepaliveTimeMs());
  channel_args.SetInt(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, rpc_options_.keepaliveTimeoutMs());
  channel_args.SetInt(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, rpc_options_.keepalivePermitWithoutCalls());

  // Create client.
  const std::string server_address = "localhost:50051";
  const auto channel = grpc::CreateCustomChannel(server_address, grpc::InsecureChannelCredentials(), channel_args);

  // Check if channel is connected.
  if (channel->GetState(true) == GRPC_CHANNEL_TRANSIENT_FAILURE) {
    LOG(ERROR) << "Failed to connect to gRPC server at " << server_address;
  }

  return channel;
}
auto ClientTask::run() -> void {
  try {
    LOG(INFO) << "Starting client task execution";
    init();

    LOG(INFO) << "Creating gRPC channel";
    // Create channel
    const auto channel = createChannel();

    LOG(INFO) << "Creating RPC client";
    // Create client.
    const client_app::RpcClient client(channel);

    LOG(INFO) << "Sending message to server";
    // Send a message.
    const std::string message = "hello world";
    if (const auto result = client.Send(message); result != "Message received successfully") {
      LOG(ERROR) << "Failed to send message: " << message;
    } else {
      LOG(INFO) << "Message sent successfully: " << message;
    }

    exit();

  } catch (const std::exception& e) {
    LOG(ERROR) << "Exception caught: " << e.what();
  } catch (...) {
    LOG(ERROR) << "Unknown exception caught.";
  }
}
auto ClientTask::exit() -> void {
  timer_.recordEnd(true);
  LOG(INFO) << "Application finished successfully.";
}
auto ClientTask::logClientInfo() -> void {
  LOG(INFO) << fox::SystemInfo::GetOSVersion();
  LOG(INFO) << fox::SystemInfo::GetCpuModelFromRegistry();
}
}  // namespace app_client
auto YAML::convert<app_client::GrpcOptions>::decode(const Node& node, app_client::GrpcOptions& rhs) -> bool {
  rhs.keepalivePermitWithoutCalls(node["keepalivePermitWithoutCalls"].as<int>());
  rhs.keepaliveTimeMs(node["keepaliveTimeMs"].as<int>());
  rhs.keepaliveTimeoutMs(node["keepaliveTimeoutMs"].as<int>());
  return true;
}
auto YAML::convert<app_client::GrpcOptions>::encode(const app_client::GrpcOptions& rhs) -> Node {
  Node node;
  node["keepalivePermitWithoutCalls"] = rhs.keepalivePermitWithoutCalls();
  node["keepaliveTimeMs"] = rhs.keepaliveTimeMs();
  node["keepaliveTimeoutMs"] = rhs.keepaliveTimeoutMs();
  return node;
}