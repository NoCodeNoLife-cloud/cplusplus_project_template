#include <glog/logging.h>

#include "HeartbeatClient.hpp"
#include "aop/LauncherAspect.hpp"

auto mainTask() -> bool
{
    const client_app::HeartbeatClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    client.SendHeartbeats("client1", 5);
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
