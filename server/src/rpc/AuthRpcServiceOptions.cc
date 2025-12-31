#include "AuthRpcServiceOptions.hpp"
#include <yaml-cpp/yaml.h>
#include <glog/logging.h>
#include "src/filesystem/type/YamlToolkit.hpp"

namespace app_server
{
    AuthRpcServiceOptions::AuthRpcServiceOptions() = default;

    AuthRpcServiceOptions::AuthRpcServiceOptions(const int32_t max_connection_idle_ms,
                                                 const int32_t max_connection_age_ms,
                                                 const int32_t max_connection_age_grace_ms,
                                                 const int32_t keepalive_time_ms,
                                                 const int32_t keepalive_timeout_ms,
                                                 const int32_t keepalive_permit_without_calls,
                                                 const std::string& server_address)
        : max_connection_idle_ms_(max_connection_idle_ms),
          max_connection_age_ms_(max_connection_age_ms),
          max_connection_age_grace_ms_(max_connection_age_grace_ms),
          keepalive_time_ms_(keepalive_time_ms),
          keepalive_timeout_ms_(keepalive_timeout_ms),
          keepalive_permit_without_calls_(keepalive_permit_without_calls),
          server_address_(server_address)
    {
    }

    auto AuthRpcServiceOptions::maxConnectionIdleMs() const
        -> int32_t
    {
        return max_connection_idle_ms_;
    }

    auto AuthRpcServiceOptions::maxConnectionIdleMs(const int32_t value)
        -> void
    {
        max_connection_idle_ms_ = value;
    }

    auto AuthRpcServiceOptions::maxConnectionAgeMs() const
        -> int32_t
    {
        return max_connection_age_ms_;
    }

    auto AuthRpcServiceOptions::maxConnectionAgeMs(const int32_t value)
        -> void
    {
        max_connection_age_ms_ = value;
    }

    auto AuthRpcServiceOptions::maxConnectionAgeGraceMs() const
        -> int32_t
    {
        return max_connection_age_grace_ms_;
    }

    auto AuthRpcServiceOptions::maxConnectionAgeGraceMs(const int32_t value)
        -> void
    {
        max_connection_age_grace_ms_ = value;
    }

    auto AuthRpcServiceOptions::keepaliveTimeMs() const
        -> int32_t
    {
        return keepalive_time_ms_;
    }

    auto AuthRpcServiceOptions::keepaliveTimeMs(const int32_t value)
        -> void
    {
        keepalive_time_ms_ = value;
    }

    auto AuthRpcServiceOptions::keepaliveTimeoutMs() const
        -> int32_t
    {
        return keepalive_timeout_ms_;
    }

    auto AuthRpcServiceOptions::keepaliveTimeoutMs(const int32_t value)
        -> void
    {
        keepalive_timeout_ms_ = value;
    }

    auto AuthRpcServiceOptions::keepalivePermitWithoutCalls() const
        -> int32_t
    {
        return keepalive_permit_without_calls_;
    }

    auto AuthRpcServiceOptions::keepalivePermitWithoutCalls(const int32_t value)
        -> void
    {
        keepalive_permit_without_calls_ = value;
    }

    // ReSharper disable once CppDFAConstantFunctionResult
    auto AuthRpcServiceOptions::serverAddress() const
        -> const std::string&
    {
        return server_address_;
    }

    auto AuthRpcServiceOptions::serverAddress(const std::string& value)
        -> void
    {
        server_address_ = value;
    }

    [[nodiscard]] auto AuthRpcServiceOptions::deserializedFromYamlFile(const std::filesystem::path& path)
        -> bool
    {
        if (!std::filesystem::exists(path))
        {
            LOG(ERROR) << "Configuration file does not exist: " << path.string();
            return false;
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
            LOG(ERROR) << "Failed to parse YAML file '" << path.string() << "': " << e.what();
            return false;
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Error processing configuration file '" << path.string() << "': " << e.what();
            return false;
        }

        return validateParameters();
    }

    [[nodiscard]] auto AuthRpcServiceOptions::validateParameters() const
        -> bool
    {
        bool is_valid = true;

        // Validate max connection idle time
        if (max_connection_idle_ms_ <= 0)
        {
            LOG(WARNING) << "Invalid max connection idle time: " << max_connection_idle_ms_
                << "ms. Using default value of 3600000ms.";
        }

        // Validate max connection age
        if (max_connection_age_ms_ <= 0)
        {
            LOG(WARNING) << "Invalid max connection age: " << max_connection_age_ms_
                << "ms. Using default value of 7200000ms.";
        }

        // Validate max connection age grace period
        if (max_connection_age_grace_ms_ < 0)
        {
            LOG(WARNING) << "Invalid max connection age grace period: " << max_connection_age_grace_ms_
                << "ms. Using default value of 300000ms.";
        }

        // Validate keepalive time (should be positive)
        if (keepalive_time_ms_ <= 0)
        {
            LOG(WARNING) << "Invalid keepalive time: " << keepalive_time_ms_
                << "ms. Using default value of 30000ms.";
        }

        // Validate keepalive timeout (should be positive)
        if (keepalive_timeout_ms_ <= 0)
        {
            LOG(WARNING) << "Invalid keepalive timeout: " << keepalive_timeout_ms_
                << "ms. Using default value of 5000ms.";
        }

        // Validate keepalive permit without calls (should be 0 or 1)
        if (keepalive_permit_without_calls_ != 0 && keepalive_permit_without_calls_ != 1)
        {
            LOG(WARNING) << "Invalid keepalive permit without calls: " << keepalive_permit_without_calls_
                << ". Valid values are 0 or 1. Using default value of 1.";
        }

        // Validate server address
        if (server_address_.empty())
        {
            LOG(WARNING) << "Server address is empty. Using default value 0.0.0.0:50051.";
        }

        // Check for potentially problematic combinations
        if (max_connection_idle_ms_ > 0 && max_connection_idle_ms_ < 1000)
        {
            LOG(WARNING) << "Max connection idle time is set to a very short interval ("
                << max_connection_idle_ms_ << "ms). This may cause excessive connection churn.";
        }

        if (keepalive_time_ms_ > 0 && keepalive_time_ms_ < 1000)
        {
            LOG(WARNING) << "Keepalive time is set to a very short interval (" << keepalive_time_ms_
                << "ms). This may cause excessive network traffic.";
        }

        if (keepalive_timeout_ms_ > 0 && keepalive_timeout_ms_ > keepalive_time_ms_)
        {
            LOG(WARNING) << "Keepalive timeout (" << keepalive_timeout_ms_
                << "ms) is greater than keepalive time (" << keepalive_time_ms_
                << "ms). This may lead to unexpected connection issues.";
        }

        // Check age vs idle time relationship
        if (max_connection_age_ms_ > 0 && max_connection_idle_ms_ > 0 &&
            max_connection_age_ms_ < max_connection_idle_ms_)
        {
            LOG(WARNING) << "Max connection age (" << max_connection_age_ms_
                << "ms) is less than max connection idle time (" << max_connection_idle_ms_
                << "ms). This may lead to unexpected connection behavior.";
        }

        return is_valid;
    }

    auto AuthRpcServiceOptions::Builder::maxConnectionIdleMs(const int32_t value)
        -> Builder&
    {
        max_connection_idle_ms_ = value;
        return *this;
    }

    auto AuthRpcServiceOptions::Builder::maxConnectionAgeMs(const int32_t value)
        -> Builder&
    {
        max_connection_age_ms_ = value;
        return *this;
    }

    auto AuthRpcServiceOptions::Builder::maxConnectionAgeGraceMs(const int32_t value)
        -> Builder&
    {
        max_connection_age_grace_ms_ = value;
        return *this;
    }

    auto AuthRpcServiceOptions::Builder::keepaliveTimeMs(const int32_t value)
        -> Builder&
    {
        keepalive_time_ms_ = value;
        return *this;
    }

    auto AuthRpcServiceOptions::Builder::keepaliveTimeoutMs(const int32_t value)
        -> Builder&
    {
        keepalive_timeout_ms_ = value;
        return *this;
    }

    auto AuthRpcServiceOptions::Builder::keepalivePermitWithoutCalls(const int32_t value)
        -> Builder&
    {
        keepalive_permit_without_calls_ = value;
        return *this;
    }

    auto AuthRpcServiceOptions::Builder::serverAddress(const std::string& value)
        -> Builder&
    {
        server_address_ = value;
        return *this;
    }

    auto AuthRpcServiceOptions::Builder::build() const
        -> AuthRpcServiceOptions
    {
        return {max_connection_idle_ms_, max_connection_age_ms_, max_connection_age_grace_ms_, keepalive_time_ms_, keepalive_timeout_ms_, keepalive_permit_without_calls_, server_address_};
    }

    auto AuthRpcServiceOptions::builder()
        -> AuthRpcServiceOptions::Builder
    {
        return Builder{};
    }
}

auto YAML::convert<app_server::AuthRpcServiceOptions>::decode(const Node& node,
                                                              app_server::AuthRpcServiceOptions& rhs)
    -> bool
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

auto YAML::convert<app_server::AuthRpcServiceOptions>::encode(const app_server::AuthRpcServiceOptions& rhs)
    -> Node
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
