#include "src/rpc/RpcClient.hpp"

#include <glog/logging.h>

namespace client_app
{
    RpcClient::RpcClient(const std::shared_ptr<grpc::Channel>& channel) : stub_(rpc::RpcService::NewStub(channel))
    {
        CHECK(channel != nullptr) << "RPC channel cannot be null";
    }
}
