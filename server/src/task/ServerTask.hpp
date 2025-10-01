#pragma once
#include <glog/logging.h>
#include <grpcpp/server_builder.h>

#include <string>

#include "src/rpc/GrpcOptions.hpp"
#include "src/time/FunctionProfiler.hpp"

namespace app_server
{
    /// @brief ServerTask is responsible for managing the main service loop
    /// @details This class coordinates various subsystems within the application server,
    /// initializes the gRPC server, loads configurations, and manages the server lifecycle.
    class ServerTask
    {
    public:
        /// @brief Construct a ServerTask with the specified name
        /// @param name The name of the server task for profiling purposes
        explicit ServerTask(std::string name);

        /// @brief Initialize the service task and its associated resources
        /// @details Sets up logging, loads configuration, and validates gRPC parameters
        auto init() -> void;

        /// @brief Run the main task
        /// @details Initializes the server, establishes gRPC connection, and starts listening
        auto run() -> void;

        /// @brief Establish a gRPC connection to the specified service
        /// @details Configures and starts the gRPC server with specified options
        auto establishGrpcConnection() -> void;

        /// @brief Exit the service task and clean up resources
        /// @details Shuts down the gRPC server and performs cleanup operations
        auto exit() const -> void;

    private:
        const std::string application_dev_config_path_ = "../../server/src/application-dev.yml";
        GrpcOptions grpc_options_;
        fox::FunctionProfiler timer_;
        std::unique_ptr<grpc::Server> server_;

        /// @brief Validate gRPC parameters for correctness
        /// @details This function checks that the gRPC parameters are within reasonable ranges
        /// and logs warnings for potentially problematic configurations
        auto validateGrpcParameters() const -> void;
    };
} // namespace app_server
