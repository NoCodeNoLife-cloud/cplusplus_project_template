#pragma once
#include <glog/logging.h>
#include <grpcpp/grpcpp.h>

#include <memory>

#include "generated/RpcService.grpc.pb.h"

namespace client_app {
/// @brief RPC client for communicating with the server.
/// @details This class provides methods to interact with the RPC service.
class RpcClient {
 public:
  explicit RpcClient(const std::shared_ptr<grpc::Channel>& channel) : stub_(rpc::RpcService::NewStub(channel)) { CHECK(channel != nullptr) << "RPC channel cannot be null"; }

  /// @brief Send a message to the server.
  /// @param message Message to send.
  /// @return Response from the server.
  [[nodiscard]] auto Send(const std::string& message) const -> std::string {
    rpc::MessageRequest request;
    request.set_content(message);

    rpc::MessageResponse response;
    grpc::ClientContext context;

    const grpc::Status status = stub_->Send(&context, request, &response);
    if (status.ok()) {
      return response.status();
    }

    LOG(ERROR) << "RPC failed with error: " << status.error_message() << " (code: " << status.error_code() << ")";
    throw std::runtime_error("RPC failed");
  }

 private:
  std::unique_ptr<rpc::RpcService::Stub> stub_{};
};
}  // namespace client_app
