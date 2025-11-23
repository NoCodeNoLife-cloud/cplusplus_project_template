#include "src/rpc/RpcClient.hpp"

#include <glog/logging.h>

namespace client_app
{
    RpcClient::RpcClient(const std::shared_ptr<grpc::Channel>& channel)
        : stub_(rpc::RpcService::NewStub(channel))
    {
        CHECK(channel != nullptr) << "RPC channel cannot be null";
    }

    auto RpcClient::RegisterUser(const std::string& username,
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

    rpc::AuthResponse RpcClient::AuthenticateUser(const std::string& username,
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

    rpc::AuthResponse RpcClient::ChangePassword(const std::string& username,
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

    rpc::AuthResponse RpcClient::ResetPassword(const std::string& username,
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

    rpc::AuthResponse RpcClient::ResetPassword(const std::string& username,
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

    rpc::AuthResponse RpcClient::DeleteUser(const std::string& username) const
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

    rpc::AuthResponse RpcClient::UserExists(const std::string& username) const
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
}
