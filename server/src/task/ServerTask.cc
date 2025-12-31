#include "src/task/ServerTask.hpp"

#include <glog/logging.h>

#include "src/GLogConfigurator.hpp"
#include "src/rpc/AuthRpcService.hpp"


namespace app_server
{
    ServerTask::ServerTask(std::string name) noexcept
        : timer_(std::move(name))
    {
    }

    ServerTask::~ServerTask() = default;

    ServerTask::ServerTask(ServerTask&&) noexcept = default;

    [[nodiscard]] auto ServerTask::init()
        -> bool
    {
        if (const glog::GLogConfigurator log_configurator{application_dev_config_path_}; !log_configurator.execute())
        {
            LOG(ERROR) << "Failed to configure GLog with config path: " << application_dev_config_path_;
            return false;
        }

        LOG(INFO) << "Initializing ServerTask with config path: " << application_dev_config_path_;
        LOG(INFO) << "GLog configuration initialized successfully";

        LOG(INFO) << "Loading gRPC configuration from: " << application_dev_config_path_;
        if (!grpc_options_.deserializedFromYamlFile(application_dev_config_path_))
        {
            LOG(ERROR) << "Failed to deserialize gRPC options from YAML file: " << application_dev_config_path_;
            return false;
        }

        LOG(INFO) << "gRPC configuration loaded successfully";
        LOG(INFO) << "gRPC Options - Max Connection Idle: " << grpc_options_.maxConnectionIdleMs()
            << "ms, Max Connection Age: " << grpc_options_.maxConnectionAgeMs()
            << "ms, Keepalive Time: " << grpc_options_.keepaliveTimeMs()
            << "ms, Keepalive Timeout: " << grpc_options_.keepaliveTimeoutMs()
            << "ms, Permit Without Calls: " << grpc_options_.keepalivePermitWithoutCalls()
            << ", Server Address: " << grpc_options_.serverAddress();
        LOG(INFO) << "ServerTask starting...";

        return true;
    }

    auto ServerTask::run()
        -> void
    {
        if (!init())
        {
            LOG(ERROR) << "Failed to initialize ServerTask";
            throw std::runtime_error("Failed to initialize ServerTask");
        }

        if (!establishGrpcConnection())
        {
            LOG(ERROR) << "Failed to establish gRPC connection";
            exit();
            throw std::runtime_error("Failed to establish gRPC connection");
        }

        exit();
    }

    [[nodiscard]] auto ServerTask::establishGrpcConnection()
        -> bool
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
        server_app::AuthRpcService service("./users.db");
        builder.RegisterService(&service);
        LOG(INFO) << "Service registered successfully";

        LOG(INFO) << "Building and starting gRPC server";
        server_ = builder.BuildAndStart();
        if (!server_)
        {
            LOG(ERROR) << "Failed to build and start gRPC server. Server object is null.";
            LOG(ERROR) << "Check server configuration and port availability.";
            return false;
        }

        LOG(INFO) << "Server listening on " << server_address;
        LOG(INFO) << "gRPC server started and waiting for connections...";
        server_->Wait();

        LOG(INFO) << "gRPC connection established.";
        return true;
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
}
