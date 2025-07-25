#include "RpcClient.hpp"

#include <iostream>
#include <thread>
#include <generated/RpcService.grpc.pb.h>
#include <glog/logging.h>

namespace client_app
{
    RpcClient::RpcClient(const std::shared_ptr<grpc::Channel>& channel): stub_(rpc::RpcService::NewStub(channel))
    {
        CHECK(channel != nullptr);
    }

    [[noreturn]] auto RpcClient::SendHeartbeats(const std::string& client_id) const -> void
    {
        signal::HeartbeatRequest request;
        request.set_name(client_id);

        signal::HeartbeatResponse response;
        while (true)
        {
            // Create a client context
            grpc::ClientContext context;

            std::this_thread::sleep_for(std::chrono::seconds(1));
            if (grpc::Status status = stub_->SendHeartbeat(&context, request, &response); status.ok())
            {
                LOG(INFO) << "Received: " << response.status() << std::endl;
            }
            else
            {
                LOG(INFO) << "RPC failed: " << status.error_code() << ": " << status.error_message() << std::endl;
            }
        }
    }
}
