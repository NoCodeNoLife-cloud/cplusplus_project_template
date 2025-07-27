#pragma once

#include "generated/RpcService.grpc.pb.h"

namespace server_app
{
    class RpcServiceImpl final : public rpc::RpcService::Service
    {
    public:
        auto Send(grpc::ServerContext* context, const rpc::MessageRequest* request, rpc::MessageResponse* response) -> grpc::Status override;
    };
}
