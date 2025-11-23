#include "src/task/ClientTask.hpp"

#include <glog/logging.h>
#include <grpcpp/grpcpp.h>

#include "src/rpc/RpcClient.hpp"
#include "src/GLogConfigurator.hpp"
#include "src/system/SystemInfo.hpp"

namespace app_client
{
    ClientTask::ClientTask(const std::string& project_name_)
        : timer_(project_name_)
    {
        timer_.recordStart();
    }

    auto ClientTask::init()
        -> void
    {
        const glog::GLogConfigurator log_configurator{application_dev_config_path_};
        (void)log_configurator.execute(); // Explicitly discard nodiscard result
        LOG(INFO) << "Initializing GLog configuration from: " << application_dev_config_path_;
        LOG(INFO) << "GLog configuration initialized successfully";

        LOG(INFO) << "Loading RPC configuration from: " << application_dev_config_path_;
        rpc_options_.deserializedFromYamlFile(application_dev_config_path_);
        LOG(INFO) << "RPC configuration loaded successfully";
        LOG(INFO) << "RPC Options - Keepalive Time: " << rpc_options_.keepaliveTimeMs()
            << "ms, Timeout: " << rpc_options_.keepaliveTimeoutMs()
            << "ms, Permit Without Calls: " << rpc_options_.keepalivePermitWithoutCalls();

        LOG(INFO) << "Application starting...";
        logClientInfo();
        LOG(INFO) << "Initialization completed successfully";
    }

    auto ClientTask::task(const client_app::RpcClient& rpc_client)
        -> void
    {
        if (const auto response = rpc_client.RegisterUser("root", "Admin123!"); !response.success())
        {
            throw std::runtime_error("Failed to register user: " + response.message());
        }
        else
        {
            LOG(INFO) << "Registered user successfully, return value: " << response.message();
        }
    }

    auto ClientTask::run()
        -> void
    {
        try
        {
            init();

            LOG(INFO) << "Creating gRPC channel";
            // Create channel
            const auto channel = createChannel();
            LOG(INFO) << "gRPC channel created with state: " << channel->GetState(true);
            LOG(INFO) << "Creating RPC client";
            // Create client.
            const client_app::RpcClient client(channel);
            LOG(INFO) << "RPC client created successfully";

            task(client);
            LOG(INFO) << "Client task execution completed";
            exit();
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Exception caught: " << e.what();
        }
        catch (...)
        {
            LOG(ERROR) << "Unknown exception caught.";
        }
    }

    auto ClientTask::exit()
        -> void
    {
        timer_.recordEnd(true);
        LOG(INFO) << "Application finished successfully.";
    }

    auto ClientTask::logClientInfo()
        -> void
    {
        LOG(INFO) << "OS Version: " << common::SystemInfo::GetOSVersion();
        LOG(INFO) << "CPU Model: " << common::SystemInfo::GetCpuModelFromRegistry();
    }

    auto ClientTask::createChannel() const
        -> std::shared_ptr<grpc::Channel>
    {
        LOG(INFO) << "Setting up gRPC channel with custom arguments";

        // Validate gRPC parameters before using them
        validateGrpcParameters();

        // Setup channel.
        grpc::ChannelArguments channel_args;
        channel_args.SetInt(GRPC_ARG_KEEPALIVE_TIME_MS, rpc_options_.keepaliveTimeMs());
        channel_args.SetInt(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, rpc_options_.keepaliveTimeoutMs());
        channel_args.SetInt(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, rpc_options_.keepalivePermitWithoutCalls());

        LOG(INFO) << "Channel arguments set - Time: " << rpc_options_.keepaliveTimeMs()
            << "ms, Timeout: " << rpc_options_.keepaliveTimeoutMs()
            << "ms, Permit without calls: " << rpc_options_.keepalivePermitWithoutCalls();

        // Create client.
        const std::string server_address = rpc_options_.serverAddress();
        LOG(INFO) << "Creating channel to server at: " << server_address;
        const auto channel =
            grpc::CreateCustomChannel(server_address, grpc::InsecureChannelCredentials(), channel_args);

        // Wait for channel to connect with a timeout
        const auto state = channel->GetState(true);
        LOG(INFO) << "Channel state after creation: " << state;

        // Give channel some time to connect
        if (!channel->WaitForConnected(std::chrono::system_clock::now() + std::chrono::seconds(5)))
        {
            LOG(ERROR) << "Failed to connect to gRPC server at " << server_address
                << " within timeout period";
        }
        else
        {
            LOG(INFO) << "Successfully connected to gRPC server at " << server_address;
        }

        return channel;
    }

    auto ClientTask::validateGrpcParameters() const
        -> void
    {
        // Validate keepalive time (should be positive)
        if (rpc_options_.keepaliveTimeMs() <= 0)
        {
            LOG(WARNING) << "Invalid keepalive time: " << rpc_options_.keepaliveTimeMs()
                << "ms. Using default value of 30000ms.";
        }

        // Validate keepalive timeout (should be positive)
        if (rpc_options_.keepaliveTimeoutMs() <= 0)
        {
            LOG(WARNING) << "Invalid keepalive timeout: " << rpc_options_.keepaliveTimeoutMs()
                << "ms. Using default value of 5000ms.";
        }

        // Validate keepalive permit without calls (should be 0 or 1)
        if (rpc_options_.keepalivePermitWithoutCalls() != 0 && rpc_options_.keepalivePermitWithoutCalls() != 1)
        {
            LOG(WARNING) << "Invalid keepalive permit without calls: " << rpc_options_.keepalivePermitWithoutCalls()
                << ". Valid values are 0 or 1. Using default value of 1.";
        }

        // Check for potentially problematic combinations
        if (rpc_options_.keepaliveTimeMs() > 0 && rpc_options_.keepaliveTimeMs() < 1000)
        {
            LOG(WARNING) << "Keepalive time is set to a very short interval (" << rpc_options_.keepaliveTimeMs()
                << "ms). This may cause excessive network traffic.";
        }

        if (rpc_options_.keepaliveTimeoutMs() > 0 && rpc_options_.keepaliveTimeoutMs() > rpc_options_.keepaliveTimeMs())
        {
            LOG(WARNING) << "Keepalive timeout (" << rpc_options_.keepaliveTimeoutMs()
                << "ms) is greater than keepalive time (" << rpc_options_.keepaliveTimeMs()
                << "ms). This may lead to unexpected connection issues.";
        }

        // Validate server address
        if (rpc_options_.serverAddress().empty())
        {
            LOG(WARNING) << "Server address is empty. Using default value localhost:50051.";
        }
    }
} // namespace app_client
