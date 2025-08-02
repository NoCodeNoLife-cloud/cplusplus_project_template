#include "RpcClient.hpp"

#include <generated/RpcService.grpc.pb.h>
#include <glog/logging.h>

namespace client_app {
RpcClient::RpcClient(const std::shared_ptr<grpc::Channel>& channel) : stub_(rpc::RpcService::NewStub(channel)) { CHECK(channel != nullptr) << "RPC channel cannot be null"; }

auto RpcClient::Send(const std::string& message) const -> std::string {
  rpc::MessageRequest request;
  request.set_content(message);

  rpc::MessageResponse response;
  grpc::ClientContext context;

  const grpc::Status status = stub_->Send(&context, request, &response);
  if (status.ok()) {
    return response.status();
  }

  LOG(ERROR) << "RPC failed with error: " << status.error_message() << " (code: " << status.error_code() << ")";
  return "RPC failed";
}
}  // namespace client_app
