#pragma once
#include <src/auth/UserAuthenticator.hpp>
#include <src/exception/AuthenticationException.hpp>

#include "generated/RpcService.grpc.pb.h"
#include <string>

namespace server_app
{
    /// @brief RPC service implementation for handling remote procedure calls
    /// @details This class implements the gRPC service interface defined in RpcService.grpc.pb.h
    /// and provides the actual business logic for handling RPC requests.
    class RpcServiceImpl final : public rpc::RpcService::Service
    {
    public:
        /// @brief Constructor with database path
        /// @param db_path Path to SQLite database file
        explicit RpcServiceImpl(const std::string& db_path) noexcept;

        /// @brief Default destructor
        ~RpcServiceImpl() noexcept override = default;

        /// @brief Copy constructor (deleted)
        RpcServiceImpl(const RpcServiceImpl&) = delete;

        /// @brief Copy assignment operator (deleted)
        auto operator=(const RpcServiceImpl&)
            -> RpcServiceImpl& = delete;

        /// @brief Move constructor (deleted)
        RpcServiceImpl(RpcServiceImpl&&) = delete;

        /// @brief Move assignment operator (deleted)
        auto operator=(RpcServiceImpl&&)
            -> RpcServiceImpl& = delete;

        /// @brief Register new user account
        [[nodiscard]] auto RegisterUser(::grpc::ServerContext* context,
                          const ::rpc::RegisterUserRequest* request,
                          ::rpc::AuthResponse* response)
            -> ::grpc::Status override;

        /// @brief Authenticate user credentials
        [[nodiscard]] auto AuthenticateUser(::grpc::ServerContext* context,
                              const ::rpc::AuthenticateUserRequest* request,
                              ::rpc::AuthResponse* response)
            -> ::grpc::Status override;

        /// @brief Change user password
        [[nodiscard]] auto ChangePassword(::grpc::ServerContext* context,
                            const ::rpc::ChangePasswordRequest* request,
                            ::rpc::AuthResponse* response)
            -> ::grpc::Status override;

        /// @brief Reset user password (administrative)
        [[nodiscard]] auto ResetPassword(::grpc::ServerContext* context,
                           const ::rpc::ResetPasswordRequest* request,
                           ::rpc::AuthResponse* response)
            -> ::grpc::Status override;

        /// @brief Delete user account
        [[nodiscard]] auto DeleteUser(::grpc::ServerContext* context,
                        const ::rpc::DeleteUserRequest* request,
                        ::rpc::AuthResponse* response)
            -> ::grpc::Status override;

        /// @brief Check if user exists
        [[nodiscard]] auto UserExists(::grpc::ServerContext* context,
                        const ::rpc::UserExistsRequest* request,
                        ::rpc::AuthResponse* response)
            -> ::grpc::Status override;

    private:
        /// @brief Authenticator instance for managing user accounts
        common::UserAuthenticator authenticator_;

        /// @brief Map exception types to error codes using table-driven approach
        static const std::unordered_map<std::string_view, int> error_map_;

        /// @brief Convert AuthenticationException to grpc::Status
        /// @param e AuthenticationException to handle
        /// @param response Response to populate with error details
        /// @return Appropriate gRPC status
        [[nodiscard]] static auto HandleAuthException(const common::AuthenticationException& e,
                                        ::rpc::AuthResponse* response) noexcept
            -> ::grpc::Status;
    };
} // namespace server_app
