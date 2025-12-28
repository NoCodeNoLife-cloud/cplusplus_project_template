#include "src/task/GrpcOptions.hpp"

#include <glog/logging.h>

namespace app_client
{
    GrpcOptions::GrpcOptions(const int32_t keepalive_time_ms,
                             const int32_t keepalive_timeout_ms,
                             const int32_t keepalive_permit_without_calls,
                             std::string server_address)
        : keepalive_time_ms_(keepalive_time_ms), keepalive_timeout_ms_(keepalive_timeout_ms), keepalive_permit_without_calls_(keepalive_permit_without_calls), server_address_(std::move(server_address))
    {
    }

    auto GrpcOptions::Builder::keepaliveTimeMs(const int32_t value)
        -> Builder&
    {
        keepalive_time_ms_ = value;
        return *this;
    }

    auto GrpcOptions::Builder::keepaliveTimeoutMs(const int32_t value)
        -> Builder&
    {
        keepalive_timeout_ms_ = value;
        return *this;
    }

    auto GrpcOptions::Builder::keepalivePermitWithoutCalls(const int32_t value)
        -> Builder&
    {
        keepalive_permit_without_calls_ = value;
        return *this;
    }

    auto GrpcOptions::Builder::serverAddress(const std::string& value)
        -> Builder&
    {
        server_address_ = value;
        return *this;
    }

    auto GrpcOptions::Builder::build() const
        -> GrpcOptions
    {
        GrpcOptions options = {keepalive_time_ms_, keepalive_timeout_ms_, keepalive_permit_without_calls_, server_address_};
        options.validate(); // Validate parameters after construction
        return options;
    }

    GrpcOptions::Builder GrpcOptions::builder()
    {
        return {};
    }

    auto GrpcOptions::keepaliveTimeMs() const
        -> int32_t
    {
        return keepalive_time_ms_;
    }

    auto GrpcOptions::keepaliveTimeMs(const int32_t value)
        -> void
    {
        keepalive_time_ms_ = value;
        validate(); // Validate after setting new value
    }

    auto GrpcOptions::keepaliveTimeoutMs() const
        -> int32_t
    {
        return keepalive_timeout_ms_;
    }

    auto GrpcOptions::keepaliveTimeoutMs(const int32_t value)
        -> void
    {
        keepalive_timeout_ms_ = value;
        validate(); // Validate after setting new value
    }

    auto GrpcOptions::keepalivePermitWithoutCalls() const
        -> int32_t
    {
        return keepalive_permit_without_calls_;
    }

    auto GrpcOptions::keepalivePermitWithoutCalls(const int32_t value)
        -> void
    {
        keepalive_permit_without_calls_ = value;
        validate(); // Validate after setting new value
    }

    // ReSharper disable once CppDFAConstantFunctionResult
    auto GrpcOptions::serverAddress() const
        -> const std::string&
    {
        return server_address_;
    }

    auto GrpcOptions::serverAddress(const std::string& value)
        -> void
    {
        server_address_ = value;
        validate(); // Validate after setting new value
    }

    auto GrpcOptions::deserializedFromYamlFile(const std::filesystem::path& path)
        -> bool
    {
        if (!std::filesystem::exists(path))
        {
            throw std::runtime_error("Configuration file does not exist: " + path.string());
        }

        try
        {
            const YAML::Node root = common::YamlToolkit::read(path.string());
            const YAML::Node grpcNode = common::YamlToolkit::getNodeOrRoot(root, "grpc");

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

        validate(); // Validate after loading from YAML
        return true;
    }

    auto GrpcOptions::validate() const noexcept
        -> void
    {
        LOG(INFO) << "Validating gRPC parameters";

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

        // Check for potentially problematic combinations
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

        // Validate server address
        if (server_address_.empty())
        {
            LOG(WARNING) << "Server address is empty. Using default value localhost:50051.";
        }

        LOG(INFO) << "gRPC parameter validation completed";
    }
}

auto YAML::convert<app_client::GrpcOptions>::decode(const Node& node,
                                                    app_client::GrpcOptions& rhs)
    -> bool
{
    rhs.keepaliveTimeMs(node["keepaliveTimeMs"].as<int32_t>());
    rhs.keepaliveTimeoutMs(node["keepaliveTimeoutMs"].as<int32_t>());
    rhs.keepalivePermitWithoutCalls(node["keepalivePermitWithoutCalls"].as<int32_t>());
    rhs.serverAddress(node["serverAddress"].as<std::string>());
    return true;
}

auto YAML::convert<app_client::GrpcOptions>::encode(const app_client::GrpcOptions& rhs)
    -> Node
{
    Node node;
    node["keepaliveTimeMs"] = rhs.keepaliveTimeMs();
    node["keepaliveTimeoutMs"] = rhs.keepaliveTimeoutMs();
    node["keepalivePermitWithoutCalls"] = rhs.keepalivePermitWithoutCalls();
    node["serverAddress"] = rhs.serverAddress();
    return node;
}
