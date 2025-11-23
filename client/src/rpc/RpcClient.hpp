#pragma once
#include <memory>
#include <grpcpp/grpcpp.h>

#include "generated/RpcService.grpc.pb.h"

namespace client_app
{
    /// @brief RPC client for communicating with the server.
    /// @details This class provides methods to interact with the RPC service.
    class RpcClient
    {
    public:
        explicit RpcClient(const std::shared_ptr<grpc::Channel>& channel);

        /// @brief Send a message to the server.
        /// @param message Message to send.
        /// @return Response from the server.
        [[nodiscard]] auto Send(const std::string& message) const
            -> std::string;


        [[nodiscard]] auto RegisterUser(const std::string& username,
                                        const std::string& password) const
            -> rpc::AuthResponse
        {
            rpc::RegisterUserRequest request;
            request.set_username(username);
            request.set_password(password);

            rpc::AuthResponse response;
            grpc::ClientContext context;

            if (const grpc::Status status = stub_->RegisterUser(&context, request, &response); !status.ok())
            {
                response.set_success(false);
                response.set_message("RPC failed: " + status.error_message());
                response.set_error_code(status.error_code());
            }
            return response;
        }

    private:
        std::unique_ptr<rpc::RpcService::Stub> stub_{};
    };
} // namespace client_app
