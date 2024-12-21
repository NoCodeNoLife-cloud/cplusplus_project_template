#include "HeartbeatServiceImpl.hpp"

#include <iostream>
#include <glog/logging.h>

namespace server_app
{
    grpc::Status HeartbeatServiceImpl::SendHeartbeat(grpc::ServerContext* context, grpc::ServerReader<rpc::HeartbeatRequest>* reader, rpc::HeartbeatResponse* response)
    {
        rpc::HeartbeatRequest req;
        int count = 0;

        while (reader->Read(&req))
        {
            std::cout << "Received heartbeat from client ID: " << req.client_id() << std::endl;
            ++count;
        }

        response->set_status("Alive (" + std::to_string(count) + " heartbeats received)");
        return grpc::Status::OK;
    }
}
