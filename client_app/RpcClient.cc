#include "RpcClient.hpp"

#include <iostream>
#include <thread>
#include <generated/RpcService.grpc.pb.h>
#include <glog/logging.h>

namespace client_app
{
    RpcClient::RpcClient(const std::shared_ptr<grpc::Channel>& channel): stub_(rpc::RpcService::NewStub(channel))
    {
        CHECK(channel != nullptr);
    }
}
