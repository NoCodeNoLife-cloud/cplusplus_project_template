#include "include/GLogParameters.hpp"
#include <yaml-cpp/yaml.h>

namespace service
{
    GLogParameters::GLogParameters(const int32_t min_log_level, std::string log_name, const bool log_to_stderr)
        : min_log_level_(min_log_level), log_name_(std::move(log_name)), log_to_stderr_(log_to_stderr)
    {
    }

    auto GLogParameters::minLogLevel() const noexcept -> int32_t
    {
        return min_log_level_;
    }

    auto GLogParameters::minLogLevel(const int32_t min_log_level) noexcept -> void
    {
        min_log_level_ = min_log_level;
    }

    auto GLogParameters::logName() const noexcept -> std::string
    {
        return log_name_;
    }

    auto GLogParameters::logName(const std::string& log_name) -> void
    {
        log_name_ = log_name;
    }

    auto GLogParameters::logToStderr() const noexcept -> bool
    {
        return log_to_stderr_;
    }

    auto GLogParameters::logToStderr(const bool log_to_stderr) noexcept -> void
    {
        log_to_stderr_ = log_to_stderr;
    }

    auto GLogParameters::deserializedFromYamlFile(const std::filesystem::path& path) -> void
    {
        if (!std::filesystem::exists(path))
        {
            throw std::runtime_error("Configuration file does not exist: " + path.string());
        }

        try
        {
            if (const YAML::Node node = YAML::LoadFile(path.string()); node["glog"])
            {
                const YAML::Node& glog_node = node["glog"];
                if (glog_node["minLogLevel"])
                {
                    min_log_level_ = glog_node["minLogLevel"].as<int32_t>();
                }
                if (glog_node["logName"])
                {
                    log_name_ = glog_node["logName"].as<std::string>();
                }
                if (glog_node["logToStderr"])
                {
                    log_to_stderr_ = glog_node["logToStderr"].as<bool>();
                }
            }
            else
            {
                // If there's no "glog" section, try to parse the fields directly from root
                if (node["minLogLevel"])
                {
                    min_log_level_ = node["minLogLevel"].as<int32_t>();
                }
                if (node["logName"])
                {
                    log_name_ = node["logName"].as<std::string>();
                }
                if (node["logToStderr"])
                {
                    log_to_stderr_ = node["logToStderr"].as<bool>();
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

    auto GLogParameters::operator==(const GLogParameters& other) const noexcept -> bool
    {
        return min_log_level_ == other.min_log_level_ &&
            log_name_ == other.log_name_ &&
            log_to_stderr_ == other.log_to_stderr_;
    }

    auto GLogParameters::operator!=(const GLogParameters& other) const noexcept -> bool
    {
        return !(*this == other);
    }
}

auto YAML::convert<service::GLogParameters>::decode(const Node& node, service::GLogParameters& rhs) -> bool
{
    if (!node.IsMap())
    {
        return false;
    }

    if (node["minLogLevel"])
    {
        rhs.minLogLevel(node["minLogLevel"].as<int32_t>());
    }
    if (node["logName"])
    {
        rhs.logName(node["logName"].as<std::string>());
    }
    if (node["logToStderr"])
    {
        rhs.logToStderr(node["logToStderr"].as<bool>());
    }
    return true;
}

auto YAML::convert<service::GLogParameters>::encode(const service::GLogParameters& rhs) -> Node
{
    Node node;
    node["minLogLevel"] = rhs.minLogLevel();
    node["logName"] = rhs.logName();
    node["logToStderr"] = rhs.logToStderr();
    return node;
}
