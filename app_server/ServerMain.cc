#include <cstdint>
#include <cstdlib>
#include <glog/logging.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/security/server_credentials.h>

#include "RpcServiceImpl.hpp"
#include "aop/LauncherAspect.hpp"
#include "generated/RpcService.grpc.pb.h"

void RunServer()
{
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
}

auto mainTask() -> bool
{
    RunServer();
    return EXIT_SUCCESS;
}

auto main(const int32_t, char*) -> int32_t
{
    try
    {
        // Launch the application.
        common::LauncherAspect launcher;
        launcher.exec(mainTask);
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << e.what();
    }
}
