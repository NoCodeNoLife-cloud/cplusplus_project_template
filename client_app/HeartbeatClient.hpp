#pragma once

#include <memory>
#include <grpcpp/grpcpp.h>

#include "generated/heartbeat.grpc.pb.h"

namespace client_app
{
    class HeartbeatClient
    {
    public:
        explicit HeartbeatClient(const std::shared_ptr<grpc::Channel>& channel);

        auto SendHeartbeats(const std::string& client_id, int num_beats) const -> void;

    private:
        std::unique_ptr<rpc::HeartbeatService::Stub> stub_;
    };
}
