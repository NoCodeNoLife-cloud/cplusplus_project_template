#include <glog/logging.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/support/channel_arguments.h>

#include <rpc/RpcClient.hpp>
#include <task/MainTask.hpp>

#include "utils/system/SystemInfo.hpp"

namespace app_client {
auto MainTask::run() -> bool {
  logClientInfo();

  // Setup channel.
  grpc::ChannelArguments channel_args;
  channel_args.SetInt(GRPC_ARG_KEEPALIVE_TIME_MS, 30000);
  channel_args.SetInt(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, 5000);
  channel_args.SetInt(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, 1);

  // Create client.
  const std::string server_address = "localhost:50051";
  const auto channel = grpc::CreateCustomChannel(
      server_address, grpc::InsecureChannelCredentials(), channel_args);

  // Check if channel is connected.
  if (channel->GetState(true) == GRPC_CHANNEL_TRANSIENT_FAILURE) {
    LOG(ERROR) << "Failed to connect to gRPC server at " << server_address;
    return EXIT_FAILURE;
  }

  // Create client.
  const client_app::RpcClient client(channel);

  try {
    // Send a message.
    LOG(INFO) << client.Send("hello world");
  } catch (const std::exception& e) {
    LOG(ERROR) << e.what();
  }

  return EXIT_SUCCESS;
}

auto MainTask::logClientInfo() -> void {
  LOG(INFO) << common::SystemInfo::GetOSVersion();
  LOG(INFO) << common::SystemInfo::GetCpuModelFromRegistry();
}
}  // namespace app_client