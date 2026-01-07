#include "RpcMetadata.hpp"

namespace common
{
    auto RpcMetadata::grpcStateToString(const grpc_connectivity_state state) -> std::string
    {
        switch (state)
        {
        case GRPC_CHANNEL_IDLE: return "IDLE";
        case GRPC_CHANNEL_CONNECTING: return "CONNECTING";
        case GRPC_CHANNEL_READY: return "READY";
        case GRPC_CHANNEL_TRANSIENT_FAILURE: return "TRANSIENT_FAILURE";
        case GRPC_CHANNEL_SHUTDOWN: return "SHUTDOWN";
        default: return "UNKNOWN";
        }
    }
} // common
