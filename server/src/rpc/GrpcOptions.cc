#include "src/rpc/GrpcOptions.hpp"
#include <yaml-cpp/yaml.h>
#include "src/filesystem/type/YamlToolkit.hpp"

namespace app_server
{
    auto GrpcOptions::maxConnectionIdleMs() const -> int32_t
    {
        return max_connection_idle_ms_;
    }

    auto GrpcOptions::maxConnectionIdleMs(const int32_t value) -> void
    {
        max_connection_idle_ms_ = value;
    }

    auto GrpcOptions::maxConnectionAgeMs() const -> int32_t
    {
        return max_connection_age_ms_;
    }

    auto GrpcOptions::maxConnectionAgeMs(const int32_t value) -> void
    {
        max_connection_age_ms_ = value;
    }

    auto GrpcOptions::maxConnectionAgeGraceMs() const -> int32_t
    {
        return max_connection_age_grace_ms_;
    }

    auto GrpcOptions::maxConnectionAgeGraceMs(const int32_t value) -> void
    {
        max_connection_age_grace_ms_ = value;
    }

    auto GrpcOptions::keepaliveTimeMs() const -> int32_t
    {
        return keepalive_time_ms_;
    }

    auto GrpcOptions::keepaliveTimeMs(const int32_t value) -> void
    {
        keepalive_time_ms_ = value;
    }

    auto GrpcOptions::keepaliveTimeoutMs() const -> int32_t
    {
        return keepalive_timeout_ms_;
    }

    auto GrpcOptions::keepaliveTimeoutMs(const int32_t value) -> void
    {
        keepalive_timeout_ms_ = value;
    }

    auto GrpcOptions::keepalivePermitWithoutCalls() const -> int32_t
    {
        return keepalive_permit_without_calls_;
    }

    auto GrpcOptions::keepalivePermitWithoutCalls(const int32_t value) -> void
    {
        keepalive_permit_without_calls_ = value;
    }

    // ReSharper disable once CppDFAConstantFunctionResult
    auto GrpcOptions::serverAddress() const -> const std::string&
    {
        return server_address_;
    }

    auto GrpcOptions::serverAddress(const std::string& value) -> void
    {
        server_address_ = value;
    }

    auto GrpcOptions::deserializedFromYamlFile(const std::filesystem::path& path) -> void
    {
        if (!std::filesystem::exists(path))
        {
            throw std::runtime_error("Configuration file does not exist: " + path.string());
        }

        try
        {
            const YAML::Node root = common::YamlToolkit::read(path.string());
            const YAML::Node grpcNode = common::YamlToolkit::getNodeOrRoot(root, "grpc");

            if (grpcNode["maxConnectionIdleMs"])
            {
                max_connection_idle_ms_ = grpcNode["maxConnectionIdleMs"].as<int32_t>();
            }
            if (grpcNode["maxConnectionAgeMs"])
            {
                max_connection_age_ms_ = grpcNode["maxConnectionAgeMs"].as<int32_t>();
            }
            if (grpcNode["maxConnectionAgeGraceMs"])
            {
                max_connection_age_grace_ms_ = grpcNode["maxConnectionAgeGraceMs"].as<int32_t>();
            }
            if (grpcNode["keepaliveTimeMs"])
            {
                keepalive_time_ms_ = grpcNode["keepaliveTimeMs"].as<int32_t>();
            }
            if (grpcNode["keepaliveTimeoutMs"])
            {
                keepalive_timeout_ms_ = grpcNode["keepaliveTimeoutMs"].as<int32_t>();
            }
            if (grpcNode["keepalivePermitWithoutCalls"])
            {
                keepalive_permit_without_calls_ = grpcNode["keepalivePermitWithoutCalls"].as<int32_t>();
            }
            if (grpcNode["serverAddress"])
            {
                server_address_ = grpcNode["serverAddress"].as<std::string>();
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
}

auto YAML::convert<app_server::GrpcOptions>::decode(const Node& node, app_server::GrpcOptions& rhs) -> bool
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

auto YAML::convert<app_server::GrpcOptions>::encode(const app_server::GrpcOptions& rhs) -> Node
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
