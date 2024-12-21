#pragma once

#include "generated/heartbeat.grpc.pb.h"
#include "generated/heartbeat.pb.h"

namespace server_app
{
    class HeartbeatServiceImpl final : public rpc::HeartbeatService::Service
    {
    public:
        grpc::Status SendHeartbeat(grpc::ServerContext* context, grpc::ServerReader<rpc::HeartbeatRequest>* reader, rpc::HeartbeatResponse* response) override;
    };
}
