#pragma once
#include <glog/logging.h>
#include <grpcpp/server_builder.h>

#include <string>
#include <utility>

#include "src/GLogConfigurator.hpp"
#include "GrpcOptions.hpp"
#include "src/filesystem/serialize/YamlObjectSerializer.hpp"
#include "rpc/RpcServiceImpl.hpp"
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
        const std::string config_path_ = "../../server/src/config/glog.yaml";
        const std::string grpc_config_path_ = "../../server/src/config/grpc.yaml";
        GrpcOptions grpc_options_;
        fox::FunctionProfiler timer_;
        std::unique_ptr<grpc::Server> server_;

        /// @brief Validate gRPC parameters for correctness
        /// @details This function checks that the gRPC parameters are within reasonable ranges
        /// and logs warnings for potentially problematic configurations
        auto validateGrpcParameters() const -> void;
    };

    inline ServerTask::ServerTask(std::string name) : timer_(std::move(name))
    {
    }

    inline auto ServerTask::init() -> void
    {
        LOG(INFO) << "Initializing ServerTask with config path: " << config_path_;
        service::GLogConfigurator log_configurator{config_path_};
        log_configurator.execute();
        LOG(INFO) << "GLog configuration initialized successfully";

        LOG(INFO) << "Loading gRPC configuration from: " << grpc_config_path_;
        grpc_options_ = fox::YamlObjectSerializer<GrpcOptions>::deserialize(grpc_config_path_);

        // Validate gRPC parameters after loading them
        validateGrpcParameters();

        LOG(INFO) << "gRPC configuration loaded successfully";
        LOG(INFO) << "gRPC Options - Max Connection Idle: " << grpc_options_.maxConnectionIdleMs()
            << "ms, Max Connection Age: " << grpc_options_.maxConnectionAgeMs()
            << "ms, Keepalive Time: " << grpc_options_.keepaliveTimeMs()
            << "ms, Keepalive Timeout: " << grpc_options_.keepaliveTimeoutMs()
            << "ms, Permit Without Calls: " << grpc_options_.keepalivePermitWithoutCalls()
            << ", Server Address: " << grpc_options_.serverAddress();
        LOG(INFO) << "ServerTask starting...";
        timer_.recordStart();
    }

    inline auto ServerTask::run() -> void
    {
        try
        {
            init();
            establishGrpcConnection();
            exit();
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Exception occurred: " << e.what();
        }
        catch (...)
        {
            LOG(ERROR) << "Unknown exception occurred.";
        }
        LOG(INFO) << "ServerTask completed.";
    }

    inline auto ServerTask::establishGrpcConnection() -> void
    {
        LOG(INFO) << "Establishing gRPC connection...";
        try
        {
            // Build the server.
            const std::string server_address = grpc_options_.serverAddress();
            LOG(INFO) << "Configuring server to listen on: " << server_address;
            grpc::ServerBuilder builder;
            builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

            // Set the keepalive parameters.
            LOG(INFO) << "Setting gRPC server channel arguments";
            builder.AddChannelArgument(GRPC_ARG_MAX_CONNECTION_IDLE_MS, grpc_options_.maxConnectionIdleMs());
            builder.AddChannelArgument(GRPC_ARG_MAX_CONNECTION_AGE_MS, grpc_options_.maxConnectionAgeMs());
            builder.AddChannelArgument(GRPC_ARG_MAX_CONNECTION_AGE_GRACE_MS, grpc_options_.maxConnectionAgeGraceMs());
            builder.AddChannelArgument(GRPC_ARG_KEEPALIVE_TIME_MS, grpc_options_.keepaliveTimeMs());
            builder.AddChannelArgument(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, grpc_options_.keepaliveTimeoutMs());
            builder.AddChannelArgument(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS,
                                       grpc_options_.keepalivePermitWithoutCalls());

            LOG(INFO) << "Channel arguments set - "
                << "Max Connection Idle: " << grpc_options_.maxConnectionIdleMs() << "ms, "
                << "Max Connection Age: " << grpc_options_.maxConnectionAgeMs() << "ms, "
                << "Max Connection Age Grace: " << grpc_options_.maxConnectionAgeGraceMs() << "ms, "
                << "Keepalive Time: " << grpc_options_.keepaliveTimeMs() << "ms, "
                << "Keepalive Timeout: " << grpc_options_.keepaliveTimeoutMs() << "ms, "
                << "Keepalive Permit Without Calls: " << grpc_options_.keepalivePermitWithoutCalls();

            server_app::RpcServiceImpl service;
            builder.RegisterService(&service);
            LOG(INFO) << "Service registered successfully";

            server_ = builder.BuildAndStart();
            if (!server_)
            {
                LOG(ERROR) << "Failed to build and start gRPC server";
                return;
            }

            LOG(INFO) << "Server listening on " << server_address;
            LOG(INFO) << "gRPC server started and waiting for connections...";
            server_->Wait();
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "gRPC server failed to start. Exception: " << e.what();
        }
        catch (...)
        {
            LOG(ERROR) << "gRPC server failed to start with unknown error.";
        }
        LOG(INFO) << "gRPC connection established.";
    }

    inline auto ServerTask::exit() const -> void
    {
        LOG(INFO) << "Shutting down service task...";
        if (server_) {
            server_->Shutdown();
            LOG(INFO) << "gRPC server shutdown complete.";
        }
        LOG(INFO) << "Service task shutdown complete.";
    }

    inline auto ServerTask::validateGrpcParameters() const -> void
    {
        // Validate max connection idle time
        if (grpc_options_.maxConnectionIdleMs() <= 0)
        {
            LOG(WARNING) << "Invalid max connection idle time: " << grpc_options_.maxConnectionIdleMs()
                << "ms. Using default value of 3600000ms.";
        }

        // Validate max connection age
        if (grpc_options_.maxConnectionAgeMs() <= 0)
        {
            LOG(WARNING) << "Invalid max connection age: " << grpc_options_.maxConnectionAgeMs()
                << "ms. Using default value of 7200000ms.";
        }

        // Validate max connection age grace period
        if (grpc_options_.maxConnectionAgeGraceMs() < 0)
        {
            LOG(WARNING) << "Invalid max connection age grace period: " << grpc_options_.maxConnectionAgeGraceMs()
                << "ms. Using default value of 300000ms.";
        }

        // Validate keepalive time (should be positive)
        if (grpc_options_.keepaliveTimeMs() <= 0)
        {
            LOG(WARNING) << "Invalid keepalive time: " << grpc_options_.keepaliveTimeMs()
                << "ms. Using default value of 30000ms.";
        }

        // Validate keepalive timeout (should be positive)
        if (grpc_options_.keepaliveTimeoutMs() <= 0)
        {
            LOG(WARNING) << "Invalid keepalive timeout: " << grpc_options_.keepaliveTimeoutMs()
                << "ms. Using default value of 5000ms.";
        }

        // Validate keepalive permit without calls (should be 0 or 1)
        if (grpc_options_.keepalivePermitWithoutCalls() != 0 && grpc_options_.keepalivePermitWithoutCalls() != 1)
        {
            LOG(WARNING) << "Invalid keepalive permit without calls: " << grpc_options_.keepalivePermitWithoutCalls()
                << ". Valid values are 0 or 1. Using default value of 1.";
        }

        // Validate server address
        if (grpc_options_.serverAddress().empty())
        {
            LOG(WARNING) << "Server address is empty. Using default value 0.0.0.0:50051.";
        }

        // Check for potentially problematic combinations
        if (grpc_options_.maxConnectionIdleMs() > 0 && grpc_options_.maxConnectionIdleMs() < 1000)
        {
            LOG(WARNING) << "Max connection idle time is set to a very short interval ("
                << grpc_options_.maxConnectionIdleMs() << "ms). This may cause excessive connection churn.";
        }

        if (grpc_options_.keepaliveTimeMs() > 0 && grpc_options_.keepaliveTimeMs() < 1000)
        {
            LOG(WARNING) << "Keepalive time is set to a very short interval (" << grpc_options_.keepaliveTimeMs()
                << "ms). This may cause excessive network traffic.";
        }

        if (grpc_options_.keepaliveTimeoutMs() > 0 && grpc_options_.keepaliveTimeoutMs() > grpc_options_.
            keepaliveTimeMs())
        {
            LOG(WARNING) << "Keepalive timeout (" << grpc_options_.keepaliveTimeoutMs()
                << "ms) is greater than keepalive time (" << grpc_options_.keepaliveTimeMs()
                << "ms). This may lead to unexpected connection issues.";
        }

        // Check age vs idle time relationship
        if (grpc_options_.maxConnectionAgeMs() > 0 && grpc_options_.maxConnectionIdleMs() > 0 &&
            grpc_options_.maxConnectionAgeMs() < grpc_options_.maxConnectionIdleMs())
        {
            LOG(WARNING) << "Max connection age (" << grpc_options_.maxConnectionAgeMs()
                << "ms) is less than max connection idle time (" << grpc_options_.maxConnectionIdleMs()
                << "ms). This may lead to unexpected connection behavior.";
        }
    }
} // namespace server
