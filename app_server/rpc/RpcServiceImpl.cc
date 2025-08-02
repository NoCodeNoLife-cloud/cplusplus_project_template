#include "rpc/RpcServiceImpl.hpp"

#include <glog/logging.h>

namespace server_app {
grpc::Status RpcServiceImpl::Send(grpc::ServerContext* context, const rpc::MessageRequest* request, rpc::MessageResponse* response) {
  if (!context || !request || !response) {
    LOG(ERROR) << "Invalid input parameters: context=" << context << ", request=" << request << ", response=" << response;
    return {grpc::StatusCode::INVALID_ARGUMENT, "Invalid input parameters"};
  }

  LOG(INFO) << "Received message from client: " << request->content() << " (peer=" << context->peer() << ")";
  response->set_status("Message received successfully");
  return grpc::Status::OK;
}
}  // namespace server_app
