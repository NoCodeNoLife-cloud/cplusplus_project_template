#include "AuthRpcServiceOptions.hpp"
#include <yaml-cpp/yaml.h>
#include <glog/logging.h>
#include <sstream>
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
        validateParameters();
    }

    auto AuthRpcServiceOptions::maxConnectionIdleMs() const noexcept
        -> int32_t
    {
        return max_connection_idle_ms_;
    }

    auto AuthRpcServiceOptions::maxConnectionIdleMs(const int32_t value) noexcept
        -> void
    {
        max_connection_idle_ms_ = value;
    }

    auto AuthRpcServiceOptions::maxConnectionAgeMs() const noexcept
        -> int32_t
    {
        return max_connection_age_ms_;
    }

    auto AuthRpcServiceOptions::maxConnectionAgeMs(const int32_t value) noexcept
        -> void
    {
        max_connection_age_ms_ = value;
    }

    auto AuthRpcServiceOptions::maxConnectionAgeGraceMs() const noexcept
        -> int32_t
    {
        return max_connection_age_grace_ms_;
    }

    auto AuthRpcServiceOptions::maxConnectionAgeGraceMs(const int32_t value) noexcept
        -> void
    {
        max_connection_age_grace_ms_ = value;
    }

    auto AuthRpcServiceOptions::keepaliveTimeMs() const noexcept
        -> int32_t
    {
        return keepalive_time_ms_;
    }

    auto AuthRpcServiceOptions::keepaliveTimeMs(const int32_t value) noexcept
        -> void
    {
        keepalive_time_ms_ = value;
    }

    auto AuthRpcServiceOptions::keepaliveTimeoutMs() const noexcept
        -> int32_t
    {
        return keepalive_timeout_ms_;
    }

    auto AuthRpcServiceOptions::keepaliveTimeoutMs(const int32_t value) noexcept
        -> void
    {
        keepalive_timeout_ms_ = value;
    }

    auto AuthRpcServiceOptions::keepalivePermitWithoutCalls() const noexcept
        -> int32_t
    {
        return keepalive_permit_without_calls_;
    }

    auto AuthRpcServiceOptions::keepalivePermitWithoutCalls(const int32_t value) noexcept
        -> void
    {
        keepalive_permit_without_calls_ = value;
    }

    // ReSharper disable once CppDFAConstantFunctionResult
    auto AuthRpcServiceOptions::serverAddress() const noexcept
        -> const std::string&
    {
        return server_address_;
    }

    auto AuthRpcServiceOptions::serverAddress(const std::string& value)
        -> void
    {
        server_address_ = value;
    }

    auto AuthRpcServiceOptions::deserializedFromYamlFile(const std::filesystem::path& path)
        -> void
    {
        if (!std::filesystem::exists(path))
        {
            LOG(ERROR) << "Configuration file does not exist: " << path.string();
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
            LOG(ERROR) << "Failed to parse YAML file '" << path.string() << "': " << e.what();
            throw std::runtime_error("Failed to parse YAML file: " + std::string(e.what()));
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Error processing configuration file '" << path.string() << "': " << e.what();
            throw std::runtime_error("Error processing configuration file: " + std::string(e.what()));
        }

        validateParameters();
    }

    auto AuthRpcServiceOptions::validateParameters() const
        -> void
    {
        // Validate max connection idle time (critical error)
        if (max_connection_idle_ms_ <= 0)
        {
            LOG(ERROR) << "Invalid max connection idle time: " << max_connection_idle_ms_
                << "ms. Value must be greater than 0.";
            throw std::invalid_argument("Invalid max connection idle time: " + std::to_string(max_connection_idle_ms_) + "ms (must be > 0)");
        }

        // Validate max connection age (critical error)
        if (max_connection_age_ms_ <= 0)
        {
            LOG(ERROR) << "Invalid max connection age: " << max_connection_age_ms_
                << "ms. Value must be greater than 0.";
            throw std::invalid_argument("Invalid max connection age: " + std::to_string(max_connection_age_ms_) + "ms (must be > 0)");
        }

        // Validate max connection age grace period (critical error)
        if (max_connection_age_grace_ms_ < 0)
        {
            LOG(ERROR) << "Invalid max connection age grace period: " << max_connection_age_grace_ms_
                << "ms. Value must be greater than or equal to 0.";
            throw std::invalid_argument("Invalid max connection age grace period: " + std::to_string(max_connection_age_grace_ms_) + "ms (must be >= 0)");
        }

        // Validate keepalive time (should be positive) (critical error)
        if (keepalive_time_ms_ <= 0)
        {
            LOG(ERROR) << "Invalid keepalive time: " << keepalive_time_ms_
                << "ms. Value must be greater than 0.";
            throw std::invalid_argument("Invalid keepalive time: " + std::to_string(keepalive_time_ms_) + "ms (must be > 0)");
        }

        // Validate keepalive timeout (should be positive) (critical error)
        if (keepalive_timeout_ms_ <= 0)
        {
            LOG(ERROR) << "Invalid keepalive timeout: " << keepalive_timeout_ms_
                << "ms. Value must be greater than 0.";
            throw std::invalid_argument("Invalid keepalive timeout: " + std::to_string(keepalive_timeout_ms_) + "ms (must be > 0)");
        }

        // Validate keepalive permit without calls (should be 0 or 1) (critical error)
        if (keepalive_permit_without_calls_ != 0 && keepalive_permit_without_calls_ != 1)
        {
            LOG(ERROR) << "Invalid keepalive permit without calls: " << keepalive_permit_without_calls_
                << ". Valid values are 0 or 1.";
            throw std::invalid_argument("Invalid keepalive permit without calls: " + std::to_string(keepalive_permit_without_calls_) + " (must be 0 or 1)");
        }

        // Validate server address (critical error)
        if (server_address_.empty())
        {
            LOG(ERROR) << "Server address is empty.";
            throw std::invalid_argument("Server address is empty (must not be empty)");
        }

        // Check for potentially problematic combinations (warnings only)
        LOG_IF(WARNING, max_connection_idle_ms_ > 0 && max_connection_idle_ms_ < 1000)
            << "Max connection idle time is set to a very short interval ("
            << max_connection_idle_ms_ << "ms). This may cause excessive connection churn.";

        LOG_IF(WARNING, keepalive_time_ms_ > 0 && keepalive_time_ms_ < 1000)
            << "Keepalive time is set to a very short interval (" << keepalive_time_ms_
            << "ms). This may cause excessive network traffic.";

        LOG_IF(WARNING, keepalive_timeout_ms_ > 0 && keepalive_timeout_ms_ > keepalive_time_ms_)
            << "Keepalive timeout (" << keepalive_timeout_ms_
            << "ms) is greater than keepalive time (" << keepalive_time_ms_
            << "ms). This may lead to unexpected connection issues.";

        // Check age vs idle time relationship
        LOG_IF(WARNING, max_connection_age_ms_ > 0 && max_connection_idle_ms_ > 0 &&
               max_connection_age_ms_ < max_connection_idle_ms_)
            << "Max connection age (" << max_connection_age_ms_
            << "ms) is less than max connection idle time (" << max_connection_idle_ms_
            << "ms). This may lead to unexpected connection behavior.";
    }

    auto AuthRpcServiceOptions::Builder::maxConnectionIdleMs(const int32_t value) noexcept
        -> Builder&
    {
        max_connection_idle_ms_ = value;
        return *this;
    }

    auto AuthRpcServiceOptions::Builder::maxConnectionAgeMs(const int32_t value) noexcept
        -> Builder&
    {
        max_connection_age_ms_ = value;
        return *this;
    }

    auto AuthRpcServiceOptions::Builder::maxConnectionAgeGraceMs(const int32_t value) noexcept
        -> Builder&
    {
        max_connection_age_grace_ms_ = value;
        return *this;
    }

    auto AuthRpcServiceOptions::Builder::keepaliveTimeMs(const int32_t value) noexcept
        -> Builder&
    {
        keepalive_time_ms_ = value;
        return *this;
    }

    auto AuthRpcServiceOptions::Builder::keepaliveTimeoutMs(const int32_t value) noexcept
        -> Builder&
    {
        keepalive_timeout_ms_ = value;
        return *this;
    }

    auto AuthRpcServiceOptions::Builder::keepalivePermitWithoutCalls(const int32_t value) noexcept
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
        AuthRpcServiceOptions options{
            max_connection_idle_ms_, max_connection_age_ms_, max_connection_age_grace_ms_,
            keepalive_time_ms_, keepalive_timeout_ms_, keepalive_permit_without_calls_, server_address_
        };
        options.validateParameters();
        return options;
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
    if (node["maxConnectionIdleMs"])
    {
        rhs.maxConnectionIdleMs(node["maxConnectionIdleMs"].as<int32_t>());
    }
    if (node["maxConnectionAgeMs"])
    {
        rhs.maxConnectionAgeMs(node["maxConnectionAgeMs"].as<int32_t>());
    }
    if (node["maxConnectionAgeGraceMs"])
    {
        rhs.maxConnectionAgeGraceMs(node["maxConnectionAgeGraceMs"].as<int32_t>());
    }
    if (node["keepaliveTimeMs"])
    {
        rhs.keepaliveTimeMs(node["keepaliveTimeMs"].as<int32_t>());
    }
    if (node["keepaliveTimeoutMs"])
    {
        rhs.keepaliveTimeoutMs(node["keepaliveTimeoutMs"].as<int32_t>());
    }
    if (node["keepalivePermitWithoutCalls"])
    {
        rhs.keepalivePermitWithoutCalls(node["keepalivePermitWithoutCalls"].as<int32_t>());
    }
    if (node["serverAddress"])
    {
        rhs.serverAddress(node["serverAddress"].as<std::string>());
    }
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
