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
    const std::string server_address("0.0.0.0:50051");
    server_app::RpcServiceImpl service;
    grpc::ServerBuilder builder;

    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    const std::unique_ptr server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

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
        common::LauncherAspect launcher;
        launcher.exec(mainTask);
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << e.what();
    }
}
