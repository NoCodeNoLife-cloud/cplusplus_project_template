#pragma once
#include <glog/logging.h>

#include "generated/RpcService.grpc.pb.h"

namespace server_app
{
/// @brief RPC service implementation for handling remote procedure calls
/// @details This class implements the gRPC service interface defined in RpcService.grpc.pb.h
/// and provides the actual business logic for handling RPC requests.
class RpcServiceImpl final : public rpc::RpcService::Service
{
  public:
    /// @brief Send message to the server
    /// @param[in] context Server context
    /// @param[in] request Message request
    /// @param[out] response Message response
    /// @return Status of the operation
    auto Send(grpc::ServerContext *context, const rpc::MessageRequest *request, rpc::MessageResponse *response)
        -> grpc::Status override
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
};
} // namespace server_app
