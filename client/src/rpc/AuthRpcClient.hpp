#pragma once
#include <memory>
#include <grpcpp/grpcpp.h>

#include "generated/RpcService.grpc.pb.h"

namespace client_app
{
    /// @brief RPC client for communicating with the server.
    /// @details This class provides methods to interact with the RPC service.
    class AuthRpcClient
    {
    public:
        /// @brief Construct a new AuthRpcClient object
        /// @param channel The gRPC channel to use for communication
        explicit AuthRpcClient(const std::shared_ptr<grpc::Channel>& channel) noexcept;

        /// @brief Default constructor deleted to prevent uninitialized instances
        AuthRpcClient() = delete;

        /// @brief Copy constructor deleted to prevent copying
        AuthRpcClient(const AuthRpcClient&) = delete;

        /// @brief Move constructor
        AuthRpcClient(AuthRpcClient&&) noexcept = default;

        /// @brief Copy assignment operator deleted to prevent copying
        auto operator=(const AuthRpcClient&)
            -> AuthRpcClient& = delete;

        /// @brief Move assignment operator
        auto operator=(AuthRpcClient&&) noexcept
            -> AuthRpcClient& = default;

        /// @brief Default destructor
        ~AuthRpcClient() = default;

        /// @brief Register a new user with username and password
        /// @param username The username to register
        /// @param password The password for the user
        /// @return rpc::AuthResponse containing operation result
        [[nodiscard]] auto RegisterUser(const std::string& username,
                                        const std::string& password) const noexcept
            -> rpc::AuthResponse;

        /// @brief Authenticate a user with username and password
        /// @param username The username to authenticate
        /// @param password The password for the user
        /// @return rpc::AuthResponse containing operation result
        [[nodiscard]] auto AuthenticateUser(const std::string& username,
                                            const std::string& password) const noexcept
            -> rpc::AuthResponse;

        /// @brief Check if a user exists
        /// @param username The username to check
        /// @return rpc::AuthResponse containing operation result
        [[nodiscard]] auto UserExists(const std::string& username) const noexcept
            -> rpc::AuthResponse;

        /// @brief Change password for an authenticated user
        /// @param username The username whose password to change
        /// @param current_password The current password
        /// @param new_password The new password to set
        /// @return rpc::AuthResponse containing operation result
        [[nodiscard]] auto ChangePassword(const std::string& username,
                                          const std::string& current_password,
                                          const std::string& new_password) const noexcept
            -> rpc::AuthResponse;

        /// @brief Reset password for a user (admin function)
        /// @param username The username whose password to reset
        /// @param new_password The new password to set
        /// @return rpc::AuthResponse containing operation result
        [[nodiscard]] auto ResetPassword(const std::string& username,
                                         const std::string& new_password) const noexcept
            -> rpc::AuthResponse;

        /// @brief Delete a user
        /// @param username The username to delete
        /// @return rpc::AuthResponse containing operation result
        [[nodiscard]] auto DeleteUser(const std::string& username) const noexcept
            -> rpc::AuthResponse;

    private:
        /// @brief gRPC stub for making RPC calls
        std::unique_ptr<rpc::RpcService::Stub> stub_{};
    };
} // namespace client_app
