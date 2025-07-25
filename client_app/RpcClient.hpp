#pragma once

#include <memory>
#include <grpcpp/grpcpp.h>

#include "generated/RpcService.grpc.pb.h"

namespace client_app
{
    class RpcClient
    {
    public:
        explicit RpcClient(const std::shared_ptr<grpc::Channel>& channel);

        auto SendHeartbeats(const std::string& client_id) const -> void;

    private:
        std::unique_ptr<rpc::RpcService::Stub> stub_{};
    };
}
