#pragma once
// ReSharper disable once CppUnusedIncludeDirective
#include <grpcpp/grpcpp.h>

#include "GLogConfigurator.hpp"
#include "GrpcOptions.hpp"
#include "rpc/RpcClient.hpp"
#include "utils/system/SystemInfo.hpp"
#include "utils/time/FunctionProfiler.hpp"

namespace app_client {
/// @brief A class that represents a client task
/// @details This class is responsible for running the main task and logging client info
class ClientTask {
 public:
  explicit ClientTask(const std::string& project_name_) : timer_(project_name_) {}

  /// @brief Initialize the client task
  /// @return true if initialization was successful
  auto init() -> void {
    LOG(INFO) << "Initializing GLog configuration from: " << config_path_;
    service::GLogConfigurator log_configurator{config_path_};
    log_configurator.execute();

    LOG(INFO) << "Loading RPC configuration from: " << rpc_config_path_;
    rpc_options_ = fox::YamlObjectSerializer<GrpcOptions>::deserialize(rpc_config_path_);

    LOG(INFO) << "Application starting...";
    logClientInfo();
    LOG(INFO) << "Initialization completed successfully";
  }

  /// @brief Run the main task
  /// @return true if the task was successful
  auto run() -> void {
    try {
      LOG(INFO) << "Starting client task execution";
      init();

      LOG(INFO) << "Creating gRPC channel";
      // Create channel
      const auto channel = createChannel();

      LOG(INFO) << "Creating RPC client";
      // Create client.
      const client_app::RpcClient client(channel);

      LOG(INFO) << "Sending message to server";
      // Send a message.
      const std::string message = "hello world";
      if (const auto result = client.Send(message); result != "Message received successfully") {
        LOG(ERROR) << "Failed to send message: " << message;
      } else {
        LOG(INFO) << "Message sent successfully: " << message;
      }

      exit();

    } catch (const std::exception& e) {
      LOG(ERROR) << "Exception caught: " << e.what();
    } catch (...) {
      LOG(ERROR) << "Unknown exception caught.";
    }
  }

  /// @brief Exit the client task
  /// @return true if exit was successful
  auto exit() -> void {
    timer_.recordEnd(true);
    LOG(INFO) << "Application finished successfully.";
  }

  /// @brief Logs client info
  static auto logClientInfo() -> void {
    LOG(INFO) << fox::SystemInfo::GetOSVersion();
    LOG(INFO) << fox::SystemInfo::GetCpuModelFromRegistry();
  }

  /// @brief Create a gRPC channel with custom arguments
  /// @details This function sets up a gRPC channel with keepalive parameters and connects to the server
  /// @return A shared pointer to the created gRPC channel
  [[nodiscard]] auto createChannel() const -> std::shared_ptr<grpc::Channel> {
    // Setup channel.
    grpc::ChannelArguments channel_args;
    channel_args.SetInt(GRPC_ARG_KEEPALIVE_TIME_MS, rpc_options_.keepaliveTimeMs());
    channel_args.SetInt(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, rpc_options_.keepaliveTimeoutMs());
    channel_args.SetInt(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, rpc_options_.keepalivePermitWithoutCalls());

    // Create client.
    const std::string server_address = "localhost:50051";
    const auto channel = grpc::CreateCustomChannel(server_address, grpc::InsecureChannelCredentials(), channel_args);

    // Check if channel is connected.
    if (channel->GetState(true) == GRPC_CHANNEL_TRANSIENT_FAILURE) {
      LOG(ERROR) << "Failed to connect to gRPC server at " << server_address;
    }

    return channel;
  }

 private:
  const std::string config_path_ = "../../app_client/config/glog.yaml";
  const std::string rpc_config_path_ = "../../app_client/config/grpc.yaml";
  GrpcOptions rpc_options_;
  fox::FunctionProfiler timer_;
};
}  // namespace app_client