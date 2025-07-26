#pragma once

#include "generated/RpcService.grpc.pb.h"

namespace server_app
{
    class RpcServiceImpl final : public rpc::RpcService::Service
    {
    };
}
