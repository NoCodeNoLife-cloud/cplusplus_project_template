#pragma once
#include <string>
#include <grpc/impl/connectivity_state.h>

namespace common::rpc
{
    /// @brief Utility class for RPC metadata operations
    class RpcMetadata
    {
    public:
        /// @brief Converts gRPC connectivity state to human-readable string representation
        /// @param[in] state The gRPC connectivity state to convert
        /// @return String representation of the connectivity state
        [[nodiscard]] static auto grpcStateToString(grpc_connectivity_state state) -> std::string;
    };
}
