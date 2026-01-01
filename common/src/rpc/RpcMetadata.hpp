#pragma once
#include <string>
#include <grpc/impl/connectivity_state.h>

namespace common
{
    class RpcMetadata
    {
    public:
        [[nodiscard]] static auto grpcStateToString(grpc_connectivity_state state)
            -> std::string;
    };
}
