#pragma once
#include <yaml-cpp/node/node.h>
#include <filesystem>
#include <string>
#include <stdexcept>

#include "src/serializer/interface/IYamlConfigurable.hpp"

namespace app_server
{
    /// @brief A class that holds gRPC configuration options
    /// @details This class encapsulates all the gRPC configuration parameters
    /// that can be used to customize the behavior of gRPC channels and connections.
    /// The configuration parameters can be loaded from a YAML configuration file.
    class GrpcOptions final : public fox::IYamlConfigurable
    {
    public:
        /// @brief Get the maximum connection idle time in milliseconds
        /// @return The maximum connection idle time in milliseconds
        [[nodiscard]] inline auto maxConnectionIdleMs() const -> int32_t;

        /// @brief Set the maximum connection idle time in milliseconds
        /// @param value The maximum connection idle time in milliseconds
        inline auto maxConnectionIdleMs(int32_t value) -> void;

        /// @brief Get the maximum connection age in milliseconds
        /// @return The maximum connection age in milliseconds
        [[nodiscard]] inline auto maxConnectionAgeMs() const -> int32_t;

        /// @brief Set the maximum connection age in milliseconds
        /// @param value The maximum connection age in milliseconds
        inline auto maxConnectionAgeMs(int32_t value) -> void;

        /// @brief Get the maximum connection age grace period in milliseconds
        /// @return The maximum connection age grace period in milliseconds
        [[nodiscard]] inline auto maxConnectionAgeGraceMs() const -> int32_t;

        /// @brief Set the maximum connection age grace period in milliseconds
        /// @param value The maximum connection age grace period in milliseconds
        inline auto maxConnectionAgeGraceMs(int32_t value) -> void;

        /// @brief Get the keepalive time interval in milliseconds
        /// @return The keepalive time interval in milliseconds
        [[nodiscard]] inline auto keepaliveTimeMs() const -> int32_t;

        /// @brief Set the keepalive time interval in milliseconds
        /// @param value The keepalive time interval in milliseconds
        inline auto keepaliveTimeMs(int32_t value) -> void;

        /// @brief Get the keepalive timeout in milliseconds
        /// @return The keepalive timeout in milliseconds
        [[nodiscard]] inline auto keepaliveTimeoutMs() const -> int32_t;

        /// @brief Set the keepalive timeout in milliseconds
        /// @param value The keepalive timeout in milliseconds
        inline auto keepaliveTimeoutMs(int32_t value) -> void;

        /// @brief Check if keepalive pings are permitted without active calls
        /// @return 1 if permitted, 0 if not permitted
        [[nodiscard]] inline auto keepalivePermitWithoutCalls() const -> int32_t;

        /// @brief Set whether to permit keepalive pings without active calls
        /// @param value 1 to permit, 0 to not permit
        inline auto keepalivePermitWithoutCalls(int32_t value) -> void;

        /// @brief Get the server address
        /// @return The server address as a string
        [[nodiscard]] inline auto serverAddress() const -> const std::string&;

        /// @brief Set the server address
        /// @param value The server address as a string
        inline auto serverAddress(const std::string& value) -> void;

        /// @brief Deserialize object configuration from a YAML file
        /// @param path The file path to the YAML configuration file
        /// @throws std::runtime_error If the file cannot be read or parsed
        inline auto deserializedFromYamlFile(const std::filesystem::path& path) -> void override;

    private:
        /// @brief Maximum time a connection can remain idle before being closed (in milliseconds)
        /// @details Default value is 1 hour (60 * 60 * 1000 ms).
        int32_t max_connection_idle_ms_{60 * 60 * 1000};

        /// @brief Maximum age of a connection before it is gracefully closed (in milliseconds)
        /// @details Default value is 2 hours (2 * 60 * 60 * 1000 ms).
        int32_t max_connection_age_ms_{2 * 60 * 60 * 1000};

        /// @brief Grace period after max connection age before force closing (in milliseconds)
        /// @details Default value is 5 minutes (5 * 60 * 1000 ms).
        int32_t max_connection_age_grace_ms_{5 * 60 * 1000};

        /// @brief Time interval between keepalive pings (in milliseconds)
        /// @details This parameter controls how often the server sends keepalive pings
        /// to the client to ensure the connection is still alive.
        /// Default value is 30 seconds (30000 ms).
        int32_t keepalive_time_ms_{30 * 1000};

        /// @brief Timeout for keepalive ping acknowledgment (in milliseconds)
        /// @details This parameter controls how long the server waits for an acknowledgment
        /// of a keepalive ping from the client before considering the connection dead.
        /// Default value is 5 seconds (5000 ms).
        int32_t keepalive_timeout_ms_{5 * 1000};

        /// @brief Whether to permit keepalive pings when there are no active calls (1 = true, 0 = false)
        /// @details When set to true, keepalive pings are allowed even when there are no active RPC calls.
        /// When set to false, keepalive pings are only sent when there are active calls.
        /// Default value is true (1).
        int32_t keepalive_permit_without_calls_{1};

        /// @brief The server address to listen on
        /// @details This parameter specifies the address and port of the gRPC server
        /// Default value is 0.0.0.0:50051
        std::string server_address_{"0.0.0.0:50051"};
    };

    inline auto GrpcOptions::maxConnectionIdleMs() const -> int32_t
    {
        return max_connection_idle_ms_;
    }

    inline auto GrpcOptions::maxConnectionIdleMs(const int32_t value) -> void
    {
        max_connection_idle_ms_ = value;
    }

    inline auto GrpcOptions::maxConnectionAgeMs() const -> int32_t
    {
        return max_connection_age_ms_;
    }

    inline auto GrpcOptions::maxConnectionAgeMs(const int32_t value) -> void
    {
        max_connection_age_ms_ = value;
    }

    inline auto GrpcOptions::maxConnectionAgeGraceMs() const -> int32_t
    {
        return max_connection_age_grace_ms_;
    }

    inline auto GrpcOptions::maxConnectionAgeGraceMs(const int32_t value) -> void
    {
        max_connection_age_grace_ms_ = value;
    }

    inline auto GrpcOptions::keepaliveTimeMs() const -> int32_t
    {
        return keepalive_time_ms_;
    }

    inline auto GrpcOptions::keepaliveTimeMs(const int32_t value) -> void
    {
        keepalive_time_ms_ = value;
    }

    inline auto GrpcOptions::keepaliveTimeoutMs() const -> int32_t
    {
        return keepalive_timeout_ms_;
    }

    inline auto GrpcOptions::keepaliveTimeoutMs(const int32_t value) -> void
    {
        keepalive_timeout_ms_ = value;
    }

    inline auto GrpcOptions::keepalivePermitWithoutCalls() const -> int32_t
    {
        return keepalive_permit_without_calls_;
    }

    inline auto GrpcOptions::keepalivePermitWithoutCalls(const int32_t value) -> void
    {
        keepalive_permit_without_calls_ = value;
    }

    // ReSharper disable once CppDFAConstantFunctionResult
    inline auto GrpcOptions::serverAddress() const -> const std::string&
    {
        return server_address_;
    }

    inline auto GrpcOptions::serverAddress(const std::string& value) -> void
    {
        server_address_ = value;
    }

    inline auto GrpcOptions::deserializedFromYamlFile(const std::filesystem::path& path) -> void
    {
        if (!std::filesystem::exists(path))
        {
            throw std::runtime_error("Configuration file does not exist: " + path.string());
        }

        try
        {
            if (const YAML::Node node = YAML::LoadFile(path.string()); node["grpc"])
            {
                const YAML::Node& grpc_node = node["grpc"];
                if (grpc_node["maxConnectionIdleMs"])
                {
                    max_connection_idle_ms_ = grpc_node["maxConnectionIdleMs"].as<int32_t>();
                }
                if (grpc_node["maxConnectionAgeMs"])
                {
                    max_connection_age_ms_ = grpc_node["maxConnectionAgeMs"].as<int32_t>();
                }
                if (grpc_node["maxConnectionAgeGraceMs"])
                {
                    max_connection_age_grace_ms_ = grpc_node["maxConnectionAgeGraceMs"].as<int32_t>();
                }
                if (grpc_node["keepaliveTimeMs"])
                {
                    keepalive_time_ms_ = grpc_node["keepaliveTimeMs"].as<int32_t>();
                }
                if (grpc_node["keepaliveTimeoutMs"])
                {
                    keepalive_timeout_ms_ = grpc_node["keepaliveTimeoutMs"].as<int32_t>();
                }
                if (grpc_node["keepalivePermitWithoutCalls"])
                {
                    keepalive_permit_without_calls_ = grpc_node["keepalivePermitWithoutCalls"].as<int32_t>();
                }
                if (grpc_node["serverAddress"])
                {
                    server_address_ = grpc_node["serverAddress"].as<std::string>();
                }
            }
            else
            {
                // If there's no "grpc" section, try to parse the fields directly from root
                if (node["maxConnectionIdleMs"])
                {
                    max_connection_idle_ms_ = node["maxConnectionIdleMs"].as<int32_t>();
                }
                if (node["maxConnectionAgeMs"])
                {
                    max_connection_age_ms_ = node["maxConnectionAgeMs"].as<int32_t>();
                }
                if (node["maxConnectionAgeGraceMs"])
                {
                    max_connection_age_grace_ms_ = node["maxConnectionAgeGraceMs"].as<int32_t>();
                }
                if (node["keepaliveTimeMs"])
                {
                    keepalive_time_ms_ = node["keepaliveTimeMs"].as<int32_t>();
                }
                if (node["keepaliveTimeoutMs"])
                {
                    keepalive_timeout_ms_ = node["keepaliveTimeoutMs"].as<int32_t>();
                }
                if (node["keepalivePermitWithoutCalls"])
                {
                    keepalive_permit_without_calls_ = node["keepalivePermitWithoutCalls"].as<int32_t>();
                }
                if (node["serverAddress"])
                {
                    server_address_ = node["serverAddress"].as<std::string>();
                }
            }
        }
        catch (const YAML::Exception& e)
        {
            throw std::runtime_error("Failed to parse YAML file '" + path.string() + "': " + e.what());
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error("Error processing configuration file '" + path.string() + "': " + e.what());
        }
    }
} // namespace app_server

/// @brief YAML serialization specialization for GrpcOptions.
/// Provides methods to encode and decode GrpcOptions to/from YAML nodes.
template <>
struct YAML::convert<app_server::GrpcOptions>
{
    /// @brief Decode a YAML node into a GrpcOptions object.
    /// @param node The YAML node containing the configuration data.
    /// @param rhs The GrpcOptions object to populate.
    /// @return True if decoding was successful.
    static auto decode(const Node& node, app_server::GrpcOptions& rhs) -> bool;

    /// @brief Encode a GrpcOptions object into a YAML node.
    /// @param rhs The GrpcOptions object to encode.
    /// @return A YAML node containing the configuration data.
    static auto encode(const app_server::GrpcOptions& rhs) -> Node;
};

inline auto YAML::convert<app_server::GrpcOptions>::decode(const Node& node, app_server::GrpcOptions& rhs) -> bool
{
    rhs.maxConnectionIdleMs(node["maxConnectionIdleMs"].as<int32_t>());
    rhs.maxConnectionAgeMs(node["maxConnectionAgeMs"].as<int32_t>());
    rhs.maxConnectionAgeGraceMs(node["maxConnectionAgeGraceMs"].as<int32_t>());
    rhs.keepaliveTimeMs(node["keepaliveTimeMs"].as<int32_t>());
    rhs.keepaliveTimeoutMs(node["keepaliveTimeoutMs"].as<int32_t>());
    rhs.keepalivePermitWithoutCalls(node["keepalivePermitWithoutCalls"].as<int32_t>());
    rhs.serverAddress(node["serverAddress"].as<std::string>());
    return true;
}

inline auto YAML::convert<app_server::GrpcOptions>::encode(const app_server::GrpcOptions& rhs) -> Node
{
    Node node;
    node["maxConnectionIdleMs"] = rhs.maxConnectionIdleMs();
    node["maxConnectionAgeMs"] = rhs.maxConnectionAgeMs();
    node["maxConnectionAgeGraceMs"] = rhs.maxConnectionAgeGraceMs();
    node["keepaliveTimeMs"] = rhs.keepaliveTimeMs();
    node["keepaliveTimeoutMs"] = rhs.keepaliveTimeoutMs();
    node["keepalivePermitWithoutCalls"] = rhs.keepalivePermitWithoutCalls();
    node["serverAddress"] = rhs.serverAddress();
    return node;
}
