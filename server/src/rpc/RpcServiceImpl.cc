#include "src/rpc/RpcServiceImpl.hpp"

#include <glog/logging.h>

namespace server_app
{
    auto RpcServiceImpl::Send(grpc::ServerContext* context, const rpc::MessageRequest* request,
                              rpc::MessageResponse* response) -> grpc::Status
    {
        if (!context || !request || !response)
        {
            LOG(ERROR) << "Invalid input parameters: context=" << context << ", request=" << request
                << ", response=" << response;
            return {grpc::StatusCode::INVALID_ARGUMENT, "Invalid input parameters"};
        }

        LOG(INFO) << "Received message from client: " << request->content() << " (peer=" << context->peer() << ")";
        response->set_status("Message received successfully");
        return grpc::Status::OK;
    }
} // namespace server_app
