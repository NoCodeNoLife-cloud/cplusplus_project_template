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
        auto Send(const std::string& message) const -> std::string;

    private:
        std::unique_ptr<rpc::RpcService::Stub> stub_{};
    };
}
