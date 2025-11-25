#include "src/task/ClientTask.hpp"

#include <glog/logging.h>
#include <grpcpp/grpcpp.h>

#include "src/GLogConfigurator.hpp"
#include "src/filesystem/io/Console.hpp"
#include "src/rpc/RpcClient.hpp"
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
        LOG(INFO) << "Starting authentication process";

        const common::Console console;
        // Authenticate user
        LOG(INFO) << "Please enter your username: ";
        const std::string username = common::Console::readLine();
        LOG(INFO) << "Please enter your password: ";
        const std::string password = common::Console::readLine();
        LOG(INFO) << "Login attempt for user:  " << username;
        if (const auto authenticateUserResponse = rpc_client.AuthenticateUser(username, password); !authenticateUserResponse.success())
        {
            LOG(ERROR) << "Authentication failed: " << authenticateUserResponse.message();

            // Check if user exists, if not ask to create a new account
            LOG(INFO) << "User does not exist, do you want to create a new account? [y/n] ";
            if (const auto createNewAccount = common::Console::readLine(); createNewAccount == "y" or createNewAccount == "Y")
            {
                LOG(INFO) << "Registering user...";
                if (const auto registerUserResponse = rpc_client.RegisterUser("root", "Admin123!"); !registerUserResponse.success())
                {
                    LOG(ERROR) << "Failed to register user: " << registerUserResponse.message()
                        << ", Error code: " << registerUserResponse.error_code();
                    throw std::runtime_error("Failed to register user: " + registerUserResponse.message());
                }
                else
                {
                    LOG(INFO) << "Registered user successfully, return value: " << registerUserResponse.message();
                }
            }
        }
        else
        {
            LOG(INFO) << "User authenticated successfully";
        }
        LOG(INFO) << "Authentication process completed";

        if (const auto deleteUserResponse = rpc_client.DeleteUser(username); !deleteUserResponse.success())
        {
            LOG(ERROR) << "Failed to delete user: " << deleteUserResponse.message() << ", Error code: " << deleteUserResponse.error_code();
        }
        else
        {
            LOG(INFO) << "Deleted user successfully, return value: " << deleteUserResponse.message();
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
            LOG(ERROR) << "Stack trace: " << google::ProgramInvocationShortName() << " " << typeid(e).name();
        }
        catch (...)
        {
            LOG(ERROR) << "Unknown exception caught.";
            LOG(ERROR) << "Stack trace not available for unknown exception type";
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
        LOG(INFO) << "Memory Details: " << common::SystemInfo::GetMemoryDetails();
        LOG(INFO) << "Graphics Card Info: " << common::SystemInfo::GetGraphicsCardInfo();
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
            LOG(INFO) << "Connection attempt finished with state: " << channel->GetState(false);
        }
        else
        {
            LOG(INFO) << "Successfully connected to gRPC server at " << server_address;
            LOG(INFO) << "Final connection state: " << channel->GetState(false);
        }

        return channel;
    }

    auto ClientTask::validateGrpcParameters() const
        -> void
    {
        LOG(INFO) << "Validating gRPC parameters";

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

        LOG(INFO) << "gRPC parameter validation completed";
    }
} // namespace app_client
