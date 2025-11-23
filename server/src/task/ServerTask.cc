#include "src/task/ServerTask.hpp"

#include "src/rpc/RpcServiceImpl.hpp"
#include "src/GLogConfigurator.hpp"

namespace app_server
{
    ServerTask::ServerTask(std::string name)
        : timer_(std::move(name))
    {
    }

    auto ServerTask::init()
        -> void
    {
        if (const glog::GLogConfigurator log_configurator{application_dev_config_path_}; !log_configurator.execute())
        {
            LOG(ERROR) << "Failed to configure GLog with config path: " << application_dev_config_path_;
            throw std::runtime_error("Failed to configure GLog");
        };
        LOG(INFO) << "Initializing ServerTask with config path: " << application_dev_config_path_;
        LOG(INFO) << "GLog configuration initialized successfully";

        LOG(INFO) << "Loading gRPC configuration from: " << application_dev_config_path_;
        grpc_options_.deserializedFromYamlFile(application_dev_config_path_);

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
    }

    auto ServerTask::run()
        -> void
    {
        try
        {
            init();
            establishGrpcConnection();
            exit();
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Exception occurred in ServerTask::run(): " << e.what();
            LOG(ERROR) << "Exception type: " << typeid(e).name();
        }
        catch (...)
        {
            LOG(ERROR) << "Unknown exception occurred in ServerTask::run().";
        }
        LOG(INFO) << "ServerTask completed.";
    }

    auto ServerTask::establishGrpcConnection()
        -> void
    {
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

            LOG(INFO) << "Registering RPC service implementation";
            server_app::RpcServiceImpl service;
            builder.RegisterService(&service);
            LOG(INFO) << "Service registered successfully";

            LOG(INFO) << "Building and starting gRPC server";
            server_ = builder.BuildAndStart();
            if (!server_)
            {
                LOG(ERROR) << "Failed to build and start gRPC server. Server object is null.";
                LOG(ERROR) << "Check server configuration and port availability.";
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

    auto ServerTask::exit() const
        -> void
    {
        LOG(INFO) << "Shutting down service task...";
        if (server_)
        {
            LOG(INFO) << "Initiating gRPC server shutdown";
            server_->Shutdown();
            LOG(INFO) << "gRPC server shutdown complete.";
        }
        else
        {
            LOG(WARNING) << "Server object is null during shutdown. Nothing to shutdown.";
        }
        LOG(INFO) << "Service task shutdown complete.";
    }

    auto ServerTask::validateGrpcParameters() const
        -> void
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
} // namespace app_server
