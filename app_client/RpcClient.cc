#include "RpcClient.hpp"

#include <generated/RpcService.grpc.pb.h>
#include <glog/logging.h>

namespace client_app
{
    RpcClient::RpcClient(const std::shared_ptr<grpc::Channel>& channel): stub_(rpc::RpcService::NewStub(channel))
    {
        CHECK(channel != nullptr);
    }

    auto RpcClient::Send(const std::string& message) const -> std::string
    {
        rpc::MessageRequest request;
        request.set_content(message);

        rpc::MessageResponse response;
        grpc::ClientContext context;

        if (const grpc::Status status = stub_->Send(&context, request, &response); status.ok())
        {
            return response.status();
        }
        return "RPC failed";
    }
}
