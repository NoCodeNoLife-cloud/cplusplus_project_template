#pragma once
#include <grpcpp/server_builder.h>

#include <string>
#include <memory>

#include "src/rpc/AuthRpcServiceOptions.hpp"
#include "src/time/FunctionProfiler.hpp"

namespace app_server
{
    /// @brief ServerTask is responsible for managing the main service loop
    /// @details This class coordinates various subsystems within the application server,
    /// initializes the gRPC server, loads configurations, and manages the server lifecycle.
    class ServerTask final
    {
    public:
        /// @brief Construct a ServerTask with the specified name
        /// @param name The name of the server task for profiling purposes
        explicit ServerTask(std::string name) noexcept;

        /// @brief Destructor shuts down the server if running
        ~ServerTask();

        /// @brief Copy constructor deleted to prevent copying
        ServerTask(const ServerTask&) = delete;

        /// @brief Move constructor
        ServerTask(ServerTask&&) noexcept;

        /// @brief Copy assignment operator deleted to prevent copying
        auto operator=(const ServerTask&)
            -> ServerTask& = delete;

        /// @brief Move assignment operator
        auto operator=(ServerTask&&)
            -> ServerTask& = delete;

        /// @brief Initialize the service task and its associated resources
        /// @details Sets up logging, loads configuration, and validates gRPC parameters
        [[nodiscard]] auto init()
            -> bool;

        /// @brief Run the main task
        /// @details Initializes the server, establishes gRPC connection, and starts listening
        auto run()
            -> void;

        /// @brief Exit the service task and clean up resources
        /// @details Shuts down the gRPC server and performs cleanup operations
        auto exit() const
            -> void;

    private:
        const std::string application_dev_config_path_{"../../server/src/application-dev.yml"};
        AuthRpcServiceOptions grpc_options_;
        common::FunctionProfiler timer_;
        std::unique_ptr<grpc::Server> server_;

        /// @brief Establish a gRPC connection to the specified service
        /// @details Configures and starts the gRPC server with specified options
        [[nodiscard]] auto establishGrpcConnection()
            -> bool;
    };
}
