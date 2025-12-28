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
        /// @brief Construct a new RpcClient object
        /// @param channel The gRPC channel to use for communication
        explicit RpcClient(const std::shared_ptr<grpc::Channel>& channel) noexcept;

        /// @brief Default constructor deleted to prevent uninitialized instances
        RpcClient() = delete;

        /// @brief Copy constructor deleted to prevent copying
        RpcClient(const RpcClient&) = delete;

        /// @brief Move constructor
        RpcClient(RpcClient&&) noexcept = default;

        /// @brief Copy assignment operator deleted to prevent copying
        auto operator=(const RpcClient&) -> RpcClient& = delete;

        /// @brief Move assignment operator
        auto operator=(RpcClient&&) noexcept -> RpcClient& = default;

        /// @brief Default destructor
        ~RpcClient() = default;

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
