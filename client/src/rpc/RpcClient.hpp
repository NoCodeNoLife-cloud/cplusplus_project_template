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

        [[nodiscard]] rpc::AuthResponse AuthenticateUser(const std::string& username,
                                                         const std::string& password) const
        {
            rpc::AuthenticateUserRequest request;
            request.set_username(username);
            request.set_password(password);

            rpc::AuthResponse response;
            grpc::ClientContext context;

            if (const grpc::Status status = stub_->AuthenticateUser(&context, request, &response); !status.ok())
            {
                response.set_success(false);
                response.set_message("RPC failed: " + status.error_message());
                response.set_error_code(status.error_code());
            }
            return response;
        }

        [[nodiscard]] rpc::AuthResponse ChangePassword(const std::string& username,
                                                       const std::string& current_password,
                                                       const std::string& new_password) const
        {
            rpc::ChangePasswordRequest request;
            request.set_username(username);
            request.set_current_password(current_password);
            request.set_new_password(new_password);

            rpc::AuthResponse response;
            grpc::ClientContext context;

            if (const grpc::Status status = stub_->ChangePassword(&context, request, &response); !status.ok())
            {
                response.set_success(false);
                response.set_message("RPC failed: " + status.error_message());
                response.set_error_code(status.error_code());
            }
            return response;
        }

        [[nodiscard]] rpc::AuthResponse ResetPassword(const std::string& username,
                                                      const std::string& new_password) const
        {
            rpc::ResetPasswordRequest request;
            request.set_username(username);
            request.set_new_password(new_password);

            rpc::AuthResponse response;
            grpc::ClientContext context;

            if (const grpc::Status status = stub_->ResetPassword(&context, request, &response); !status.ok())
            {
                response.set_success(false);
                response.set_message("RPC failed: " + status.error_message());
                response.set_error_code(status.error_code());
            }
            return response;
        }

        rpc::AuthResponse ResetPassword(const std::string& username,
                                        const std::string& new_password)
        {
            rpc::ResetPasswordRequest request;
            request.set_username(username);
            request.set_new_password(new_password);

            rpc::AuthResponse response;
            grpc::ClientContext context;

            if (const grpc::Status status = stub_->ResetPassword(&context, request, &response); !status.ok())
            {
                response.set_success(false);
                response.set_message("RPC failed: " + status.error_message());
                response.set_error_code(status.error_code());
            }
            return response;
        }

        [[nodiscard]] rpc::AuthResponse DeleteUser(const std::string& username) const
        {
            rpc::DeleteUserRequest request;
            request.set_username(username);

            rpc::AuthResponse response;
            grpc::ClientContext context;

            if (const grpc::Status status = stub_->DeleteUser(&context, request, &response); !status.ok())
            {
                response.set_success(false);
                response.set_message("RPC failed: " + status.error_message());
                response.set_error_code(status.error_code());
            }
            return response;
        }

        [[nodiscard]] rpc::AuthResponse UserExists(const std::string& username) const
        {
            rpc::DeleteUserRequest request;
            request.set_username(username);

            rpc::AuthResponse response;
            grpc::ClientContext context;

            if (const grpc::Status status = stub_->UserExists(&context, request, &response); !status.ok())
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
