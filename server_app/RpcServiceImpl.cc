#include "RpcServiceImpl.hpp"

#include <glog/logging.h>

namespace server_app
{
    grpc::Status RpcServiceImpl::SendHeartbeat(grpc::ServerContext* context, const signal::HeartbeatRequest* request, signal::HeartbeatResponse* response)
    {
        LOG(INFO) << "Received heartbeat request from " << request->name();
        const std::string reply("Hi, this is the reply");
        response->set_status(reply);
        return grpc::Status::OK;
    }
}
