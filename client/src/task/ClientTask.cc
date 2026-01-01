#include "src/task/ClientTask.hpp"

#include <glog/logging.h>
#include <grpcpp/grpcpp.h>

#include "src/GLogConfigurator.hpp"
#include "src/filesystem/io/Console.hpp"
#include "src/rpc/AuthRpcClient.hpp"
#include "src/system/SystemInfo.hpp"

namespace app_client
{
    ClientTask::ClientTask(const std::string& project_name_) noexcept
        : rpc_options_{AuthRpcClientOptions::builder().build()}
          , timer_{project_name_}
    {
        timer_.recordStart();
    }

    auto ClientTask::init() const noexcept
        -> void
    {
        const glog::GLogConfigurator log_configurator{application_dev_config_path_};
        log_configurator.execute();
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

    auto ClientTask::logIn(const client_app::AuthRpcClient& auth_rpc_client)
        -> std::string
    {
        LOG(INFO) << "Starting authentication process";

        // Authenticate user
        LOG(INFO) << "Please enter your username: ";
        const std::string username = common::Console::readLine();
        LOG(INFO) << "Please enter your password: ";
        const std::string password = common::Console::readLine();
        LOG(INFO) << "Login attempt for user: " << username;

        // Try to authenticate user
        const auto authenticateUserResponse = auth_rpc_client.AuthenticateUser(username, password);
        if (authenticateUserResponse.success())
        {
            LOG(INFO) << "User authenticated successfully";
            LOG(INFO) << "Authentication process completed";
            return username;
        }

        LOG(ERROR) << "Authentication failed: " << authenticateUserResponse.message();

        // Check if user exists.
        if (const auto userExistsResponse = auth_rpc_client.UserExists(username); !userExistsResponse.success())
        {
            // User doesn't exist, ask if they want to create a new account.
            if (shouldCreateNewAccount())
            {
                registerNewUser(auth_rpc_client, username, password);
                LOG(INFO) << "Registered user successfully";
            }
            else
            {
                LOG(INFO) << "Authentication failed, please check your username and password.";
            }
        }

        LOG(INFO) << "Authentication process completed";
        return username;
    }

    auto ClientTask::shouldCreateNewAccount()
        -> bool
    {
        LOG(INFO) << "User does not exist, do you want to create a new account? [y/n] ";
        const std::string createNewAccount = common::Console::readLine();
        return createNewAccount == "y" || createNewAccount == "Y";
    }

    auto ClientTask::registerNewUser(const client_app::AuthRpcClient& auth_rpc_client,
                                     const std::string& username,
                                     const std::string& password)
        -> void
    {
        LOG(INFO) << "Registering user...";
        const auto registerUserResponse = auth_rpc_client.RegisterUser(username, password);
        if (!registerUserResponse.success())
        {
            LOG(ERROR) << "Failed to register user: " << registerUserResponse.message()
                << ", Error code: " << registerUserResponse.error_code();
            throw std::runtime_error("Failed to register user: " + registerUserResponse.message());
        }

        LOG(INFO) << "Registered user successfully, return value: " << registerUserResponse.message();
    }

    auto ClientTask::logOut(const client_app::AuthRpcClient& auth_rpc_client,
                            const std::string& username) noexcept
        -> void
    {
        if (const auto deleteUserResponse = auth_rpc_client.DeleteUser(username); !deleteUserResponse.success())
        {
            LOG(ERROR) << "Failed to delete user: " << deleteUserResponse.message()
                << ", Error code: " << deleteUserResponse.error_code();
        }
        else
        {
            LOG(INFO) << "Deleted user successfully, return value: " << deleteUserResponse.message();
        }
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    auto ClientTask::task(const client_app::AuthRpcClient& auth_rpc_client) noexcept
        -> void
    {
        // TODO: Implement actual task logic here
    }

    auto ClientTask::run()
        -> void
    {
        init();
        const auto client = createRpcClient();
        const std::string username = logIn(client);

        task(client);
        LOG(INFO) << "Client task execution completed";

        logOut(client, username);
        exit();
    }

    auto ClientTask::createRpcClient() const
        -> client_app::AuthRpcClient
    {
        LOG(INFO) << "Creating gRPC channel";
        // Create channel using the existing createChannel method with custom arguments
        const auto channel = createChannel();
        LOG(INFO) << "gRPC channel created with state: " << channel->GetState(true);
        LOG(INFO) << "Creating RPC client";
        // Create client using the channel with custom arguments
        client_app::AuthRpcClient client{channel};
        LOG(INFO) << "RPC client created successfully";

        return std::move(client);
    }

    auto ClientTask::exit() const noexcept
        -> void
    {
        timer_.recordEnd(true);
        LOG(INFO) << "Application finished successfully.";
    }

    auto ClientTask::logClientInfo() noexcept
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

        // Setup channel
        grpc::ChannelArguments channel_args;
        channel_args.SetInt(GRPC_ARG_KEEPALIVE_TIME_MS, rpc_options_.keepaliveTimeMs());
        channel_args.SetInt(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, rpc_options_.keepaliveTimeoutMs());
        channel_args.SetInt(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, rpc_options_.keepalivePermitWithoutCalls());

        LOG(INFO) << "Channel arguments set - Time: " << rpc_options_.keepaliveTimeMs()
            << "ms, Timeout: " << rpc_options_.keepaliveTimeoutMs()
            << "ms, Permit without calls: " << rpc_options_.keepalivePermitWithoutCalls();

        // Create client
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
            throw std::runtime_error("Failed to connect to gRPC server at " + server_address + " within timeout period");
        }
        LOG(INFO) << "Successfully connected to gRPC server at " << server_address;
        LOG(INFO) << "Final connection state: " << channel->GetState(false);

        return channel;
    }
}
