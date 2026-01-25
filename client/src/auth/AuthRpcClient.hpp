#pragma once
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>

#include "generated/RpcService.grpc.pb.h"

namespace client_app::auth {
    /// @brief RPC client for communicating with the server.
    /// @details This class provides methods to interact with the RPC service.
    class AuthRpcClient {
    public:
        /// @brief Default constructor explicitly deleted to enforce parameterized construction
        AuthRpcClient() = delete;

        /// @brief Construct a new AuthRpcClient object
        /// @param channel The gRPC channel to use for communication
        explicit AuthRpcClient(const std::shared_ptr<grpc::Channel> &channel) noexcept;

        /// @brief Copy constructor deleted to enforce unique ownership semantics
        AuthRpcClient(const AuthRpcClient &) = delete;

        /// @brief Move constructor with noexcept guarantee for efficient resource transfer
        AuthRpcClient(AuthRpcClient &&) noexcept = default;

        /// @brief Copy assignment operator deleted to prevent unintended resource duplication
        auto operator=(const AuthRpcClient &) -> AuthRpcClient & = delete;

        /// @brief Move assignment operator with noexcept guarantee
        auto operator=(AuthRpcClient &&) noexcept -> AuthRpcClient & = default;

        /// @brief Virtual destructor with default implementation for proper polymorphic cleanup
        virtual ~AuthRpcClient() noexcept = default;

        /// @brief Register a new user with username and password
        /// @param[in] username The username to register
        /// @param[in] password The password for the user
        /// @return rpc::AuthResponse containing operation result
        [[nodiscard]] auto RegisterUser(const std::string &username, const std::string &password) const noexcept -> rpc::AuthResponse;

        /// @brief Authenticate a user with username and password
        /// @param[in] username The username to authenticate
        /// @param[in] password The password for the user
        /// @return rpc::AuthResponse containing operation result
        [[nodiscard]] auto AuthenticateUser(const std::string &username, const std::string &password) const noexcept -> rpc::AuthResponse;

        /// @brief Check if a user exists
        /// @param[in] username The username to check
        /// @return rpc::AuthResponse containing operation result
        [[nodiscard]] auto UserExists(const std::string &username) const noexcept -> rpc::AuthResponse;

        /// @brief Change password for an authenticated user
        /// @param[in] username The username whose password to change
        /// @param[in] current_password The current password
        /// @param[in] new_password The new password to set
        /// @return rpc::AuthResponse containing operation result
        [[nodiscard]] auto ChangePassword(const std::string &username, const std::string &current_password, const std::string &new_password) const noexcept -> rpc::AuthResponse;

        /// @brief Reset password for a user (admin function)
        /// @param[in] username The username whose password to reset
        /// @param[in] new_password The new password to set
        /// @return rpc::AuthResponse containing operation result
        [[nodiscard]] auto ResetPassword(const std::string &username, const std::string &new_password) const noexcept -> rpc::AuthResponse;

        /// @brief Delete a user
        /// @param[in] username The username to delete
        /// @return rpc::AuthResponse containing operation result
        [[nodiscard]] auto DeleteUser(const std::string &username) const noexcept -> rpc::AuthResponse;

    private:
        /// @brief Execute RPC call with error handling and logging
        /// @tparam RequestType Type of the request message
        /// @tparam ResponseType Type of the response message
        /// @param[in] operation_name Name of the operation for logging
        /// @param[in] request The request message to send
        /// @param[in] rpc_call Function that performs the actual RPC call
        /// @return rpc::AuthResponse containing operation result
        template<typename RequestType, typename ResponseType>
        [[nodiscard]] auto ExecuteRpcCall(const std::string &operation_name, const RequestType &request, const std::function<grpc::Status(grpc::ClientContext *, const RequestType &, ResponseType *)> &rpc_call) const noexcept -> ResponseType;

        /// @brief gRPC stub for making RPC calls
        std::unique_ptr<rpc::AuthService::Stub> stub_;
    };
} // namespace client_app
