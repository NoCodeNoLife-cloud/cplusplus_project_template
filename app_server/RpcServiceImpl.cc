#include "RpcServiceImpl.hpp"

#include <glog/logging.h>

namespace server_app
{
    grpc::Status RpcServiceImpl::Send(grpc::ServerContext* context, const rpc::MessageRequest* request, rpc::MessageResponse* response)
    {
        LOG(INFO) << "Received message: " << request->content();
        response->set_status("Message received successfully");
        return grpc::Status::OK;
    }
}
