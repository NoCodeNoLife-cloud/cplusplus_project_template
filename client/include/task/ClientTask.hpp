#pragma once
#include <grpcpp/grpcpp.h>

#include "GrpcOptions.hpp"
#include "include/time/FunctionProfiler.hpp"

namespace app_client
{
    /// @brief A class that represents a client task
    /// @details This class is responsible for running the main task and logging client info
    class ClientTask
    {
    public:
        /// @brief Construct a ClientTask with the specified project name
        /// @param project_name_ The name of the project for profiling purposes
        explicit ClientTask(const std::string& project_name_);

        /// @brief Initialize the client task
        /// @details Sets up logging, loads configuration, and logs system information
        /// @return void
        auto init() -> void;

        /// @brief Run the main task
        /// @details Initializes the client, creates a gRPC channel, sends a message to the server,
        /// and exits cleanly
        /// @return void
        auto run() -> void;

        /// @brief Exit the client task
        /// @details Records the end time and logs completion
        /// @return void
        auto exit() -> void;

        /// @brief Logs client system information
        /// @details Logs OS version and CPU model to the application log
        static auto logClientInfo() -> void;

        /// @brief Create a gRPC channel with custom arguments
        /// @details This function sets up a gRPC channel with keepalive parameters and connects to the server
        /// @return A shared pointer to the created gRPC channel
        [[nodiscard]] auto createChannel() const -> std::shared_ptr<grpc::Channel>;

    private:
        const std::string application_dev_config_path_ = "../../client/src/application-dev.yml";
        GrpcOptions rpc_options_;
        fox::FunctionProfiler timer_;

        /// @brief Validate gRPC parameters for correctness
        /// @details This function checks that the gRPC parameters are within reasonable ranges
        /// and logs warnings for potentially problematic configurations
        auto validateGrpcParameters() const -> void;
    };
} // namespace app_client

