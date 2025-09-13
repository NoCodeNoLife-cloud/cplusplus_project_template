#pragma once
#include <yaml-cpp/node/node.h>

namespace app_server {
/// @brief A class that holds gRPC configuration options
class GrpcOptions {
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

 public:
  // Getters
  /// @brief Get the maximum connection idle time in milliseconds
  /// @return The maximum connection idle time in milliseconds
  [[nodiscard]] auto maxConnectionIdleMs() const -> int32_t { return max_connection_idle_ms_; }

  /// @brief Get the maximum connection age in milliseconds
  /// @return The maximum connection age in milliseconds
  [[nodiscard]] auto maxConnectionAgeMs() const -> int32_t { return max_connection_age_ms_; }

  /// @brief Get the maximum connection age grace period in milliseconds
  /// @return The maximum connection age grace period in milliseconds
  [[nodiscard]] auto maxConnectionAgeGraceMs() const -> int32_t { return max_connection_age_grace_ms_; }

  /// @brief Get the keepalive time interval in milliseconds
  /// @return The keepalive time interval in milliseconds
  [[nodiscard]] auto keepaliveTimeMs() const -> int32_t { return keepalive_time_ms_; }

  /// @brief Get the keepalive timeout in milliseconds
  /// @return The keepalive timeout in milliseconds
  [[nodiscard]] auto keepaliveTimeoutMs() const -> int32_t { return keepalive_timeout_ms_; }

  /// @brief Check if keepalive pings are permitted without active calls
  /// @return 1 if permitted, 0 if not permitted
  [[nodiscard]] auto keepalivePermitWithoutCalls() const -> int32_t { return keepalive_permit_without_calls_; }

  // Setters
  /// @brief Set the maximum connection idle time in milliseconds
  /// @param value The maximum connection idle time in milliseconds
  auto maxConnectionIdleMs(const int32_t value) -> void { max_connection_idle_ms_ = value; }

  /// @brief Set the maximum connection age in milliseconds
  /// @param value The maximum connection age in milliseconds
  auto maxConnectionAgeMs(const int32_t value) -> void { max_connection_age_ms_ = value; }

  /// @brief Set the maximum connection age grace period in milliseconds
  /// @param value The maximum connection age grace period in milliseconds
  auto maxConnectionAgeGraceMs(const int32_t value) -> void { max_connection_age_grace_ms_ = value; }

  /// @brief Set the keepalive time interval in milliseconds
  /// @param value The keepalive time interval in milliseconds
  auto keepaliveTimeMs(const int32_t value) -> void { keepalive_time_ms_ = value; }

  /// @brief Set the keepalive timeout in milliseconds
  /// @param value The keepalive timeout in milliseconds
  auto keepaliveTimeoutMs(const int32_t value) -> void { keepalive_timeout_ms_ = value; }

  /// @brief Set whether to permit keepalive pings without active calls
  /// @param value 1 to permit, 0 to not permit
  auto keepalivePermitWithoutCalls(const int32_t value) -> void { keepalive_permit_without_calls_ = value; }
};
}  // namespace app_server

/// @brief YAML serialization specialization for GrpcOptions.
/// Provides methods to encode and decode GrpcOptions to/from YAML nodes.
template <>
struct YAML::convert<app_server::GrpcOptions> {
  /// @brief Decode a YAML node into a GrpcOptions object.
  /// @param node The YAML node containing the configuration data.
  /// @param rhs The GrpcOptions object to populate.
  /// @return True if decoding was successful.
  static auto decode(const Node& node, app_server::GrpcOptions& rhs) -> bool {
    rhs.maxConnectionIdleMs(node["maxConnectionIdleMs"].as<int32_t>());
    rhs.maxConnectionAgeMs(node["maxConnectionAgeMs"].as<int32_t>());
    rhs.maxConnectionAgeGraceMs(node["maxConnectionAgeGraceMs"].as<int32_t>());
    rhs.keepaliveTimeMs(node["keepaliveTimeMs"].as<int32_t>());
    rhs.keepaliveTimeoutMs(node["keepaliveTimeoutMs"].as<int32_t>());
    rhs.keepalivePermitWithoutCalls(node["keepalivePermitWithoutCalls"].as<int32_t>());
    return true;
  }

  /// @brief Encode a GrpcOptions object into a YAML node.
  /// @param rhs The GrpcOptions object to encode.
  /// @return A YAML node containing the configuration data.
  static auto encode(const app_server::GrpcOptions& rhs) -> Node {
    Node node;
    node["maxConnectionIdleMs"] = rhs.maxConnectionIdleMs();
    node["maxConnectionAgeMs"] = rhs.maxConnectionAgeMs();
    node["maxConnectionAgeGraceMs"] = rhs.maxConnectionAgeGraceMs();
    node["keepaliveTimeMs"] = rhs.keepaliveTimeMs();
    node["keepaliveTimeoutMs"] = rhs.keepaliveTimeoutMs();
    node["keepalivePermitWithoutCalls"] = rhs.keepalivePermitWithoutCalls();
    return node;
  }
};