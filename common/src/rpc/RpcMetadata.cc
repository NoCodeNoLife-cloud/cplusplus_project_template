#include "RpcMetadata.hpp"
#include <unordered_map>
#include <utility>

namespace common::rpc {
    auto RpcMetadata::grpcStateToString(const grpc_connectivity_state state) -> std::string {
        // Using table-driven approach for better maintainability
        static const std::unordered_map<grpc_connectivity_state, std::string> stateToStringMap = {{GRPC_CHANNEL_IDLE, "IDLE"}, {GRPC_CHANNEL_CONNECTING, "CONNECTING"}, {GRPC_CHANNEL_READY, "READY"}, {GRPC_CHANNEL_TRANSIENT_FAILURE, "TRANSIENT_FAILURE"}, {GRPC_CHANNEL_SHUTDOWN, "SHUTDOWN"}};

        // Look up the state in our map
        const auto it = stateToStringMap.find(state);
        if (it != stateToStringMap.end()) {
            // Found a matching state, return its string representation
            return it->second;
        }
        // State not found in map, return default unknown value
        return "UNKNOWN";
    }

    auto RpcMetadata::grpcStateToEnum(const grpc_connectivity_state state) -> GrpcConnectivityState {
        // Map grpc_connectivity_state to our internal GrpcConnectivityState enum
        switch (state) {
            case GRPC_CHANNEL_IDLE: return GrpcConnectivityState::IDLE;
            case GRPC_CHANNEL_CONNECTING: return GrpcConnectivityState::CONNECTING;
            case GRPC_CHANNEL_READY: return GrpcConnectivityState::READY;
            case GRPC_CHANNEL_TRANSIENT_FAILURE: return GrpcConnectivityState::TRANSIENT_FAILURE;
            case GRPC_CHANNEL_SHUTDOWN: return GrpcConnectivityState::SHUTDOWN;
            default:
                // Return IDLE as default for unknown states
                return GrpcConnectivityState::IDLE;
        }
    }

    auto RpcMetadata::grpcStateToString(const GrpcConnectivityState state) -> std::string {
        // Convert our internal GrpcConnectivityState enum to string
        switch (state) {
            case GrpcConnectivityState::IDLE: return "IDLE";
            case GrpcConnectivityState::CONNECTING: return "CONNECTING";
            case GrpcConnectivityState::READY: return "READY";
            case GrpcConnectivityState::TRANSIENT_FAILURE: return "TRANSIENT_FAILURE";
            case GrpcConnectivityState::SHUTDOWN: return "SHUTDOWN";
            default: return "UNKNOWN";
        }
    }
} // common
