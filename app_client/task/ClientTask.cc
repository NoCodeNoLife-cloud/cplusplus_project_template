#include <glog/logging.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/support/channel_arguments.h>

#include <rpc/RpcClient.hpp>
#include <task/ClientTask.hpp>

#include "utils/system/SystemInfo.hpp"

namespace app_client {
auto ClientTask::run() -> bool {
  logClientInfo();

  // Setup channel.
  grpc::ChannelArguments channel_args;
  channel_args.SetInt(GRPC_ARG_KEEPALIVE_TIME_MS, 30000);
  channel_args.SetInt(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, 5000);
  channel_args.SetInt(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, 1);

  // Create client.
  const std::string server_address = "localhost:50051";
  const auto channel = grpc::CreateCustomChannel(server_address, grpc::InsecureChannelCredentials(), channel_args);

  // Check if channel is connected.
  if (channel->GetState(true) == GRPC_CHANNEL_TRANSIENT_FAILURE) {
    LOG(ERROR) << "Failed to connect to gRPC server at " << server_address;
    return EXIT_FAILURE;
  }

  // Create client.
  const client_app::RpcClient client(channel);

  // Send a message.
  const std::string message = "hello world";
  if (const auto result = client.Send(message); result != "Message received successfully") {
    LOG(ERROR) << "Failed to send message: " << message;
    return EXIT_FAILURE;
  }

  timer_.recordEnd(true);
  return EXIT_SUCCESS;
}

auto ClientTask::logClientInfo() -> void {
  LOG(INFO) << common::SystemInfo::GetOSVersion();
  LOG(INFO) << common::SystemInfo::GetCpuModelFromRegistry();
}
}  // namespace app_client