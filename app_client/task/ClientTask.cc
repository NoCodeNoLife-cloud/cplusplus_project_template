#include <glog/logging.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/support/channel_arguments.h>

#include <rpc/RpcClient.hpp>
#include <task/ClientTask.hpp>

#include "log/GLogConfigurator.hpp"
#include "utils/system/SystemInfo.hpp"

namespace app_client {
auto ClientTask::RpcOptions::getKeepaliveTimeMs() const -> int { return keepalive_time_ms_; }

auto ClientTask::RpcOptions::getKeepaliveTimeoutMs() const -> int { return keepalive_timeout_ms_; }

auto ClientTask::RpcOptions::getKeepalivePermitWithoutCalls() const -> int { return keepalive_permit_without_calls_; }

auto ClientTask::RpcOptions::setKeepaliveTimeMs(const int value) -> void { keepalive_time_ms_ = value; }

auto ClientTask::RpcOptions::setKeepaliveTimeoutMs(const int value) -> void { keepalive_timeout_ms_ = value; }

auto ClientTask::RpcOptions::setKeepalivePermitWithoutCalls(const int value) -> void { keepalive_permit_without_calls_ = value; }

auto ClientTask::init() -> void {
  service::GLogConfigurator log_configurator;
  log_configurator.execute();

  LOG(INFO) << "Application starting...";
  logClientInfo();
}

auto ClientTask::createChannel() const -> std::shared_ptr<grpc::Channel> {
  // Setup channel.
  grpc::ChannelArguments channel_args;
  channel_args.SetInt(GRPC_ARG_KEEPALIVE_TIME_MS, rpc_options_.getKeepaliveTimeMs());
  channel_args.SetInt(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, rpc_options_.getKeepaliveTimeoutMs());
  channel_args.SetInt(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, rpc_options_.getKeepalivePermitWithoutCalls());

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
    init();

    // Create channel
    const auto channel = createChannel();

    // Create client.
    const client_app::RpcClient client(channel);

    // Send a message.
    const std::string message = "hello world";
    if (const auto result = client.Send(message); result != "Message received successfully") {
      LOG(ERROR) << "Failed to send message: " << message;
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
  LOG(INFO) << common::SystemInfo::GetOSVersion();
  LOG(INFO) << common::SystemInfo::GetCpuModelFromRegistry();
}
}  // namespace app_client