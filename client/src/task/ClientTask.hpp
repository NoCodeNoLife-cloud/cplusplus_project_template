#pragma once
#include <grpcpp/grpcpp.h>
#include <memory>
#include <string>

#include "GrpcOptions.hpp"
#include "src/rpc/RpcClient.hpp"
#include "src/time/FunctionProfiler.hpp"

namespace app_client
{
    class ClientTask final
    {
    public:
        /// @brief Construct a ClientTask with the specified project name
        /// @param project_name_ The name of the project for profiling purposes
        explicit ClientTask(const std::string& project_name_) noexcept;

        /// @brief Destructor
        ~ClientTask() = default;

        /// @brief Copy constructor (deleted)
        ClientTask(const ClientTask&) = delete;

        /// @brief Move constructor (deleted)
        ClientTask(ClientTask&&) = delete;

        /// @brief Copy assignment operator (deleted)
        auto operator=(const ClientTask&)
            -> ClientTask& = delete;

        /// @brief Move assignment operator (deleted)
        auto operator=(ClientTask&&)
            -> ClientTask& = delete;

        /// @brief Initialize the client task
        /// @details Sets up logging, loads configuration, and logs system information
        auto init() const noexcept
            -> void;

        /// @brief Logs a message indicating that the client is logging in
        /// @param rpc_client Reference to the RPC client for authentication
        /// @return Username of the authenticated user
        static auto logIn(const client_app::RpcClient& rpc_client)
            -> std::string;

        /// @brief Logs a message indicating that the client is logging out
        /// @param rpc_client Reference to the RPC client for logout operations
        /// @param username Username of the user to log out
        static auto logOut(const client_app::RpcClient& rpc_client,
                           const std::string& username) noexcept
            -> void;

        /// @brief Main task
        /// @param rpc_client Reference to the RPC client for executing tasks
        static auto task(const client_app::RpcClient& rpc_client) noexcept
            -> void;

        /// @brief Run the main task
        /// @details Initializes the client, creates a gRPC channel, sends a message to the server,
        /// and exits cleanly
        auto run() const
            -> void;

        /// @brief Exit the client task
        /// @details Records the end time and logs completion
        auto exit() const noexcept
            -> void;

    private:
        /// @brief Logs client system information
        /// @details Logs OS version and CPU model to the application log
        static auto logClientInfo() noexcept
            -> void;

        /// @brief Create a gRPC channel with custom arguments
        /// @details This function sets up a gRPC channel with keepalive parameters and connects to the server
        /// @return A shared pointer to the created gRPC channel
        [[nodiscard]] auto createChannel() const
            -> std::shared_ptr<grpc::Channel>;

        /// @brief Validate gRPC parameters for correctness
        /// @details This function checks that the gRPC parameters are within reasonable ranges
        /// and logs warnings for potentially problematic configurations
        auto validateGrpcParameters() const noexcept
            -> void;

        const std::string application_dev_config_path_{"../../client/src/application-dev.yml"};
        mutable GrpcOptions rpc_options_;
        mutable common::FunctionProfiler timer_;
    };
} // namespace app_client
