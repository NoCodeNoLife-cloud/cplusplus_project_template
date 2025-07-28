#include <glog/logging.h>

#include "RpcClient.hpp"
#include "aop/LauncherAspect.hpp"

auto mainTask() -> bool {
  // Setup channel.
  grpc::ChannelArguments channel_args;
  channel_args.SetInt(GRPC_ARG_KEEPALIVE_TIME_MS, 30000);
  channel_args.SetInt(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, 5000);
  channel_args.SetInt(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, 1);

  // Create client.
  const client_app::RpcClient client(grpc::CreateCustomChannel(
      "localhost:50051", grpc::InsecureChannelCredentials(), channel_args));

  try {
    // Send a message.
    LOG(INFO) << client.Send("hello world");
  } catch (const std::exception& e) {
    LOG(ERROR) << e.what();
  }

  return EXIT_SUCCESS;
}

auto main(const int32_t, char*) -> int32_t {
  try {
    // Launch
    common::LauncherAspect launcher;
    launcher.exec(mainTask);
  } catch (const std::exception& e) {
    LOG(ERROR) << e.what();
  }
}
