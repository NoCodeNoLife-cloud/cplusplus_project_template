#pragma once
#include <grpcpp/grpcpp.h>

#include <memory>

#include "generated/RpcService.grpc.pb.h"

namespace client_app {
/// \brief RPC client.
class RpcClient {
 public:
  explicit RpcClient(const std::shared_ptr<grpc::Channel>& channel);
  [[nodiscard]] auto Send(const std::string& message) const -> std::string;

 private:
  std::unique_ptr<rpc::RpcService::Stub> stub_{};
};
}  // namespace client_app
