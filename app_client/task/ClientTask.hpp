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
  explicit ClientTask(const std::string& project_name_);

  /// @brief Initialize the client task
  /// @return true if initialization was successful
  auto init() -> void;

  /// @brief Run the main task
  /// @return true if the task was successful
  auto run() -> void;

  /// @brief Exit the client task
  /// @return true if exit was successful
  auto exit() -> void;

  /// @brief Logs client info
  static auto logClientInfo() -> void;

  /// @brief Create a gRPC channel with custom arguments
  /// @details This function sets up a gRPC channel with keepalive parameters and connects to the server
  /// @return A shared pointer to the created gRPC channel
  [[nodiscard]] auto createChannel() const -> std::shared_ptr<grpc::Channel>;

 private:
  const std::string config_path_ = "../../app_client/config/glog.yaml";
  const std::string rpc_config_path_ = "../../app_client/config/grpc.yaml";
  GrpcOptions rpc_options_;
  fox::FunctionProfiler timer_;

  /// @brief Validate gRPC parameters for correctness
  /// @details This function checks that the gRPC parameters are within reasonable ranges
  auto validateGrpcParameters() const -> void;
};

inline ClientTask::ClientTask(const std::string& project_name_) : timer_(project_name_) {}

inline auto ClientTask::init() -> void {
  LOG(INFO) << "Initializing GLog configuration from: " << config_path_;
  service::GLogConfigurator log_configurator{config_path_};
  log_configurator.execute();
  LOG(INFO) << "GLog configuration initialized successfully";

  LOG(INFO) << "Loading RPC configuration from: " << rpc_config_path_;
  rpc_options_ = fox::YamlObjectSerializer<GrpcOptions>::deserialize(rpc_config_path_);
  LOG(INFO) << "RPC configuration loaded successfully";
  LOG(INFO) << "RPC Options - Keepalive Time: " << rpc_options_.keepaliveTimeMs() << "ms, Timeout: " << rpc_options_.keepaliveTimeoutMs() << "ms, Permit Without Calls: " << rpc_options_.keepalivePermitWithoutCalls();

  LOG(INFO) << "Application starting...";
  logClientInfo();
  LOG(INFO) << "Initialization completed successfully";
}

inline auto ClientTask::run() -> void {
  try {
    LOG(INFO) << "Starting client task execution";
    init();

    LOG(INFO) << "Creating gRPC channel";
    // Create channel
    const auto channel = createChannel();
    LOG(INFO) << "gRPC channel created with state: " << channel->GetState(true);

    LOG(INFO) << "Creating RPC client";
    // Create client.
    const client_app::RpcClient client(channel);
    LOG(INFO) << "RPC client created successfully";

    LOG(INFO) << "Sending message to server";
    // Send a message.
    const std::string message = "hello world";
    LOG(INFO) << "Sending message: " << message;
    if (const auto result = client.Send(message); result != "Message received successfully") {
      LOG(ERROR) << "Failed to send message: " << message << ", Error: " << result;
    } else {
      LOG(INFO) << "Message sent successfully: " << message << ", Response: " << result;
    }

    LOG(INFO) << "Client task execution completed";
    exit();

  } catch (const std::exception& e) {
    LOG(ERROR) << "Exception caught: " << e.what();
  } catch (...) {
    LOG(ERROR) << "Unknown exception caught.";
  }
}

inline auto ClientTask::exit() -> void {
  timer_.recordEnd(true);
  LOG(INFO) << "Application finished successfully.";
}

inline auto ClientTask::logClientInfo() -> void {
  LOG(INFO) << "OS Version: " << fox::SystemInfo::GetOSVersion();
  LOG(INFO) << "CPU Model: " << fox::SystemInfo::GetCpuModelFromRegistry();
}

inline auto ClientTask::createChannel() const -> std::shared_ptr<grpc::Channel> {
  LOG(INFO) << "Setting up gRPC channel with custom arguments";

  // Validate gRPC parameters before using them
  validateGrpcParameters();

  // Setup channel.
  grpc::ChannelArguments channel_args;
  channel_args.SetInt(GRPC_ARG_KEEPALIVE_TIME_MS, rpc_options_.keepaliveTimeMs());
  channel_args.SetInt(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, rpc_options_.keepaliveTimeoutMs());
  channel_args.SetInt(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, rpc_options_.keepalivePermitWithoutCalls());

  LOG(INFO) << "Channel arguments set - Time: " << rpc_options_.keepaliveTimeMs() << "ms, Timeout: " << rpc_options_.keepaliveTimeoutMs() << "ms, Permit without calls: " << rpc_options_.keepalivePermitWithoutCalls();

  // Create client.
  const std::string server_address = "localhost:50051";
  LOG(INFO) << "Creating channel to server at: " << server_address;
  const auto channel = grpc::CreateCustomChannel(server_address, grpc::InsecureChannelCredentials(), channel_args);

  // Check if channel is connected.
  const auto state = channel->GetState(true);
  LOG(INFO) << "Channel state after creation: " << state;
  if (state == GRPC_CHANNEL_TRANSIENT_FAILURE) {
    LOG(ERROR) << "Failed to connect to gRPC server at " << server_address;
  } else if (state == GRPC_CHANNEL_READY) {
    LOG(INFO) << "Successfully connected to gRPC server at " << server_address;
  } else {
    LOG(WARNING) << "Channel to gRPC server at " << server_address << " is in state: " << state;
  }

  return channel;
}

inline auto ClientTask::validateGrpcParameters() const -> void {
  // Validate keepalive time (should be positive)
  if (rpc_options_.keepaliveTimeMs() <= 0) {
    LOG(WARNING) << "Invalid keepalive time: " << rpc_options_.keepaliveTimeMs() << "ms. Using default value of 30000ms.";
  }

  // Validate keepalive timeout (should be positive)
  if (rpc_options_.keepaliveTimeoutMs() <= 0) {
    LOG(WARNING) << "Invalid keepalive timeout: " << rpc_options_.keepaliveTimeoutMs() << "ms. Using default value of 5000ms.";
  }

  // Validate keepalive permit without calls (should be 0 or 1)
  if (rpc_options_.keepalivePermitWithoutCalls() != 0 && rpc_options_.keepalivePermitWithoutCalls() != 1) {
    LOG(WARNING) << "Invalid keepalive permit without calls: " << rpc_options_.keepalivePermitWithoutCalls() << ". Valid values are 0 or 1. Using default value of 1.";
  }

  // Check for potentially problematic combinations
  if (rpc_options_.keepaliveTimeMs() > 0 && rpc_options_.keepaliveTimeMs() < 1000) {
    LOG(WARNING) << "Keepalive time is set to a very short interval (" << rpc_options_.keepaliveTimeMs() << "ms). This may cause excessive network traffic.";
  }

  if (rpc_options_.keepaliveTimeoutMs() > 0 && rpc_options_.keepaliveTimeoutMs() > rpc_options_.keepaliveTimeMs()) {
    LOG(WARNING) << "Keepalive timeout (" << rpc_options_.keepaliveTimeoutMs() << "ms) is greater than keepalive time (" << rpc_options_.keepaliveTimeMs() << "ms). This may lead to unexpected connection issues.";
  }
}
}  // namespace app_client