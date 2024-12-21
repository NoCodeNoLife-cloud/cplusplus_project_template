#include "HeartbeatClient.hpp"

#include <iostream>
#include <thread>

namespace client_app
{
    HeartbeatClient::HeartbeatClient(const std::shared_ptr<grpc::Channel>& channel): stub_(rpc::HeartbeatService::NewStub(channel))
    {
    }

    auto HeartbeatClient::SendHeartbeats(const std::string& client_id, const int num_beats) const -> void
    {
        grpc::ClientContext context;
        rpc::HeartbeatResponse response;
        const std::unique_ptr writer(stub_->SendHeartbeat(&context, &response));

        for (int i = 0; i < num_beats; ++i)
        {
            rpc::HeartbeatRequest request;
            request.set_client_id(client_id);
            writer->Write(request);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        writer->WritesDone();

        if (const grpc::Status status = writer->Finish(); status.ok())
        {
            std::cout << "Server response: " << response.status() << std::endl;
        }
        else
        {
            std::cerr << "RPC failed: " << status.error_code() << ": " << status.error_message() << std::endl;
        }
    }
}
