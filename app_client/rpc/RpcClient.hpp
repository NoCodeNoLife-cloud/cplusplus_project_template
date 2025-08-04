#pragma once
#include <grpcpp/grpcpp.h>

#include <memory>

#include "generated/RpcService.grpc.pb.h"

namespace client_app {
/// @brief RPC client for communicating with the server.
/// @details This class provides methods to interact with the RPC service.
class RpcClient {
 public:
  explicit RpcClient(const std::shared_ptr<grpc::Channel>& channel);

  /// @brief Send a message to the server.
  /// @param message Message to send.
  /// @return Response from the server.
  [[nodiscard]] auto Send(const std::string& message) const -> std::string;

 private:
  std::unique_ptr<rpc::RpcService::Stub> stub_{};
};
}  // namespace client_app
