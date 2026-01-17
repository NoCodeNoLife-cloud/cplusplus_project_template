#include "RpcMetadata.hpp"
#include <unordered_map>
#include <utility>

namespace common::rpc
{
    auto RpcMetadata::grpcStateToString(const grpc_connectivity_state state) -> std::string
    {
        // Using table-driven approach for better maintainability
        static const std::unordered_map<grpc_connectivity_state, std::string> stateToStringMap = {{GRPC_CHANNEL_IDLE, "IDLE"}, {GRPC_CHANNEL_CONNECTING, "CONNECTING"}, {GRPC_CHANNEL_READY, "READY"}, {GRPC_CHANNEL_TRANSIENT_FAILURE, "TRANSIENT_FAILURE"}, {GRPC_CHANNEL_SHUTDOWN, "SHUTDOWN"}};

        // Look up the state in our map
        const auto it = stateToStringMap.find(state);
        if (it != stateToStringMap.end())
        {
            // Found a matching state, return its string representation
            return it->second;
        }
        // State not found in map, return default unknown value
        return "UNKNOWN";
    }
} // common
