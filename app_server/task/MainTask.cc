#include "MainTask.hpp"

#include <glog/logging.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server_builder.h>

#include <cstdlib>

#include "aop/LauncherAspect.hpp"
#include "generated/RpcService.grpc.pb.h"
#include "rpc/RpcServiceImpl.hpp"

namespace app_server {
auto MainTask::run() -> bool {
  // Build the server.
  const std::string server_address("0.0.0.0:50051");
  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

  // Set the keepalive parameters.
  builder.AddChannelArgument(GRPC_ARG_MAX_CONNECTION_IDLE_MS, 60 * 60 * 1000);
  builder.AddChannelArgument(GRPC_ARG_MAX_CONNECTION_AGE_MS, 2 * 60 * 60 * 1000);
  builder.AddChannelArgument(GRPC_ARG_MAX_CONNECTION_AGE_GRACE_MS, 5 * 60 * 1000);
  builder.AddChannelArgument(GRPC_ARG_KEEPALIVE_TIME_MS, 30 * 1000);
  builder.AddChannelArgument(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, 5 * 1000);
  builder.AddChannelArgument(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, 1);

  server_app::RpcServiceImpl service;
  builder.RegisterService(&service);

  const std::unique_ptr server(builder.BuildAndStart());
  LOG(INFO) << "Server listening on " << server_address << std::endl;

  server->Wait();
  return EXIT_SUCCESS;
}
}  // namespace app_server