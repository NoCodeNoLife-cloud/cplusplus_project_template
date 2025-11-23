#pragma once
#include <src/auth/UserAuthenticator.hpp>
#include <src/exception/AuthenticationException.hpp>

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
        auto Send(grpc::ServerContext* context,
                  const rpc::MessageRequest* request,
                  rpc::MessageResponse* response)
            -> grpc::Status override;

        /// @brief Register new user account
        auto RegisterUser(grpc::ServerContext* context,
                          const rpc::RegisterUserRequest* request,
                          rpc::AuthResponse* response)
            -> grpc::Status override;

        /// @brief Authenticate user credentials
        auto AuthenticateUser(grpc::ServerContext* context,
                              const rpc::AuthenticateUserRequest* request,
                              rpc::AuthResponse* response)
            -> grpc::Status override;

        /// @brief Change user password
        auto ChangePassword(grpc::ServerContext* context,
                            const rpc::ChangePasswordRequest* request,
                            rpc::AuthResponse* response)
            -> grpc::Status override;

        /// @brief Reset user password (administrative)
        auto ResetPassword(grpc::ServerContext* context,
                           const rpc::ResetPasswordRequest* request,
                           rpc::AuthResponse* response)
            -> grpc::Status override;

        /// @brief Delete user account
        auto DeleteUser(grpc::ServerContext* context,
                        const rpc::DeleteUserRequest* request,
                        rpc::AuthResponse* response)
            -> grpc::Status override;

        /// @brief Check if user exists
        auto UserExists(grpc::ServerContext* context,
                        const rpc::DeleteUserRequest* request,
                        rpc::AuthResponse* response)
            -> grpc::Status override;

    private:
        common::UserAuthenticator authenticator_;
        /// @brief Convert AuthenticationException to grpc::Status
        static grpc::Status HandleAuthException(const common::AuthenticationException& e,
                                                rpc::AuthResponse* response);
    };
} // namespace server_app
