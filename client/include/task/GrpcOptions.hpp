#pragma once
#include <yaml-cpp/node/node.h>
#include <filesystem>
#include <string>

#include "src/serializer/interface/IYamlConfigurable.hpp"
#include "src/filesystem/type/YamlToolkit.hpp"

namespace app_client
{
    /// @brief A class that holds gRPC configuration options for the client
    /// @details This class encapsulates all the gRPC configuration parameters
    /// that can be used to customize the behavior of gRPC channels and connections.
    /// The configuration parameters can be loaded from a YAML configuration file.
    class GrpcOptions final : public fox::IYamlConfigurable
    {
    public:
        /// @brief Get the keepalive time interval in milliseconds
        /// @return The keepalive time interval in milliseconds
        [[nodiscard]] auto keepaliveTimeMs() const -> int32_t;

        /// @brief Set the keepalive time interval in milliseconds
        /// @param value The keepalive time interval in milliseconds
        auto keepaliveTimeMs(int32_t value) -> void;

        /// @brief Get the keepalive timeout in milliseconds
        /// @return The keepalive timeout in milliseconds
        [[nodiscard]] auto keepaliveTimeoutMs() const -> int32_t;

        /// @brief Set the keepalive timeout in milliseconds
        /// @param value The keepalive timeout in milliseconds
        auto keepaliveTimeoutMs(int32_t value) -> void;

        /// @brief Check if keepalive pings are permitted without active calls
        /// @return 1 if permitted, 0 if not permitted
        [[nodiscard]] auto keepalivePermitWithoutCalls() const -> int32_t;

        /// @brief Set whether to permit keepalive pings without active calls
        /// @param value 1 to permit, 0 to not permit
        auto keepalivePermitWithoutCalls(int32_t value) -> void;

        /// @brief Get the server address
        /// @return The server address as a string
        [[nodiscard]] auto serverAddress() const -> const std::string&;

        /// @brief Set the server address
        /// @param value The server address as a string
        auto serverAddress(const std::string& value) -> void;

        /// @brief Deserialize gRPC options from a YAML file
        /// @param path Path to the YAML file containing the configuration
        /// @throws std::runtime_error If file cannot be opened or decoded
        auto deserializedFromYamlFile(const std::filesystem::path& path) -> void override;

    private:
        /// @brief Time interval between keepalive pings (in milliseconds)
        /// @details This parameter controls how often the client sends keepalive pings
        /// to the server to ensure the connection is still alive.
        /// Default value is 30 seconds (30000 ms).
        int32_t keepalive_time_ms_{30 * 1000};

        /// @brief Timeout for keepalive ping acknowledgment (in milliseconds)
        /// @details This parameter controls how long the client waits for an acknowledgment
        /// of a keepalive ping from the server before considering the connection dead.
        /// Default value is 5 seconds (5000 ms).
        int32_t keepalive_timeout_ms_{5 * 1000};

        /// @brief Whether to permit keepalive pings when there are no active calls (1 = true, 0 = false)
        /// @details When set to true, keepalive pings are allowed even when there are no active RPC calls.
        /// When set to false, keepalive pings are only sent when there are active calls.
        /// Default value is true (1).
        int32_t keepalive_permit_without_calls_{1};

        /// @brief The server address to connect to
        /// @details This parameter specifies the address and port of the gRPC server
        /// Default value is localhost:50051
        std::string server_address_{"localhost:50051"};
    };
}

/// @brief YAML serialization specialization for GrpcOptions.
/// Provides methods to encode and decode GrpcOptions to/from YAML nodes.
template <>
struct YAML::convert<app_client::GrpcOptions>
{
    /// @brief Decode a YAML node into a GrpcOptions object.
    /// @param node The YAML node containing the configuration data.
    /// @param rhs The GrpcOptions object to populate.
    /// @return True if decoding was successful.
    static auto decode(const Node& node, app_client::GrpcOptions& rhs) -> bool;

    /// @brief Encode a GrpcOptions object into a YAML node.
    /// @param rhs The GrpcOptions object to encode.
    /// @return A YAML node containing the configuration data.
    static auto encode(const app_client::GrpcOptions& rhs) -> Node;
};
