#pragma once
#include <yaml-cpp/node/node.h>

namespace app_server
{
    /// @brief A class that holds gRPC configuration options
    class GrpcOptions
    {
    public:
        /// @brief Get the maximum connection idle time in milliseconds
        /// @return The maximum connection idle time in milliseconds
        [[nodiscard]] auto maxConnectionIdleMs() const -> int32_t;

        /// @brief Get the maximum connection age in milliseconds
        /// @return The maximum connection age in milliseconds
        [[nodiscard]] auto maxConnectionAgeMs() const -> int32_t;

        /// @brief Get the maximum connection age grace period in milliseconds
        /// @return The maximum connection age grace period in milliseconds
        [[nodiscard]] auto maxConnectionAgeGraceMs() const -> int32_t;

        /// @brief Get the keepalive time interval in milliseconds
        /// @return The keepalive time interval in milliseconds
        [[nodiscard]] auto keepaliveTimeMs() const -> int32_t;

        /// @brief Get the keepalive timeout in milliseconds
        /// @return The keepalive timeout in milliseconds
        [[nodiscard]] auto keepaliveTimeoutMs() const -> int32_t;

        /// @brief Check if keepalive pings are permitted without active calls
        /// @return 1 if permitted, 0 if not permitted
        [[nodiscard]] auto keepalivePermitWithoutCalls() const -> int32_t;

        /// @brief Get the server address
        /// @return The server address as a string
        [[nodiscard]] auto serverAddress() const -> const std::string&;

        /// @brief Set the maximum connection idle time in milliseconds
        /// @param value The maximum connection idle time in milliseconds
        auto maxConnectionIdleMs(int32_t value) -> void;

        /// @brief Set the maximum connection age in milliseconds
        /// @param value The maximum connection age in milliseconds
        auto maxConnectionAgeMs(int32_t value) -> void;

        /// @brief Set the maximum connection age grace period in milliseconds
        /// @param value The maximum connection age grace period in milliseconds
        auto maxConnectionAgeGraceMs(int32_t value) -> void;

        /// @brief Set the keepalive time interval in milliseconds
        /// @param value The keepalive time interval in milliseconds
        auto keepaliveTimeMs(int32_t value) -> void;

        /// @brief Set the keepalive timeout in milliseconds
        /// @param value The keepalive timeout in milliseconds
        auto keepaliveTimeoutMs(int32_t value) -> void;

        /// @brief Set whether to permit keepalive pings without active calls
        /// @param value 1 to permit, 0 to not permit
        auto keepalivePermitWithoutCalls(int32_t value) -> void;

        /// @brief Set the server address
        /// @param value The server address as a string
        auto serverAddress(const std::string& value) -> void;

    private:
        /// @brief Maximum time a connection can remain idle before being closed (in milliseconds)
        int32_t max_connection_idle_ms_{60 * 60 * 1000};
        /// @brief Maximum age of a connection before it is gracefully closed (in milliseconds)
        int32_t max_connection_age_ms_{2 * 60 * 60 * 1000};
        /// @brief Grace period after max connection age before force closing (in milliseconds)
        int32_t max_connection_age_grace_ms_{5 * 60 * 1000};
        /// @brief Time interval between keepalive pings (in milliseconds)
        int32_t keepalive_time_ms_{30 * 1000};
        /// @brief Timeout for keepalive ping acknowledgment (in milliseconds)
        int32_t keepalive_timeout_ms_{5 * 1000};
        /// @brief Whether to permit keepalive pings when there are no active calls (1 = true, 0 = false)
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

    inline auto GrpcOptions::maxConnectionAgeMs() const -> int32_t
    {
        return max_connection_age_ms_;
    }

    inline auto GrpcOptions::maxConnectionAgeGraceMs() const -> int32_t
    {
        return max_connection_age_grace_ms_;
    }

    inline auto GrpcOptions::keepaliveTimeMs() const -> int32_t
    {
        return keepalive_time_ms_;
    }

    inline auto GrpcOptions::keepaliveTimeoutMs() const -> int32_t
    {
        return keepalive_timeout_ms_;
    }

    inline auto GrpcOptions::keepalivePermitWithoutCalls() const -> int32_t
    {
        return keepalive_permit_without_calls_;
    }

    inline auto GrpcOptions::serverAddress() const -> const std::string&
    {
        return server_address_;
    }

    inline auto GrpcOptions::maxConnectionIdleMs(const int32_t value) -> void
    {
        max_connection_idle_ms_ = value;
    }

    inline auto GrpcOptions::maxConnectionAgeMs(const int32_t value) -> void
    {
        max_connection_age_ms_ = value;
    }

    inline auto GrpcOptions::maxConnectionAgeGraceMs(const int32_t value) -> void
    {
        max_connection_age_grace_ms_ = value;
    }

    inline auto GrpcOptions::keepaliveTimeMs(const int32_t value) -> void
    {
        keepalive_time_ms_ = value;
    }

    inline auto GrpcOptions::keepaliveTimeoutMs(const int32_t value) -> void
    {
        keepalive_timeout_ms_ = value;
    }

    inline auto GrpcOptions::keepalivePermitWithoutCalls(const int32_t value) -> void
    {
        keepalive_permit_without_calls_ = value;
    }

    inline auto GrpcOptions::serverAddress(const std::string& value) -> void
    {
        server_address_ = value;
    }
} // namespace server

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
