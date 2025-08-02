#pragma once
#include "generated/RpcService.grpc.pb.h"

namespace server_app {
/// @brief RPC service implementation
class RpcServiceImpl final : public rpc::RpcService::Service {
 public:
  /// @brief Send message to the server
  /// @param[in] context Server context
  /// @param[in] request Message request
  /// @param[out] response Message response
  /// @return Status of the operation
  auto Send(grpc::ServerContext* context, const rpc::MessageRequest* request, rpc::MessageResponse* response) -> grpc::Status override;
};
}  // namespace server_app
