#pragma once

#include "generated/RpcService.grpc.pb.h"
#include "generated/RpcService.pb.h"

namespace server_app
{
    class RpcServiceImpl final : public rpc::RpcService::Service
    {
    public:
        grpc::Status SendHeartbeat(grpc::ServerContext* context, const signal::HeartbeatRequest* request, signal::HeartbeatResponse* response) override;
    };
}
