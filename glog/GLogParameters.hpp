#pragma once
#include <yaml-cpp/node/node.h>

#include <string>
#include <cstdint>

namespace service
{
    /// @brief Configuration parameters for Google Logging (glog) library.
    /// This class encapsulates all the configuration options for the glog logging system.
    /// It provides getter and setter methods for each parameter and supports YAML serialization.
    class GLogParameters final
    {
    public:
        /// @brief Default constructor.
        GLogParameters() = default;

        /// @brief Constructor with parameters.
        /// @param min_log_level Minimum log level
        /// @param log_name Log name
        /// @param log_to_stderr Whether to log to stderr
        GLogParameters(int32_t min_log_level, std::string log_name, bool log_to_stderr);

        /// @brief Get the minimum log level.
        /// @return The minimum log level as an integer.
        [[nodiscard]] auto minLogLevel() const noexcept -> int32_t;

        /// @brief Get the log name.
        /// @return The log name as a string.
        [[nodiscard]] auto logName() const noexcept -> std::string;

        /// @brief Check if logging to stderr is enabled.
        /// @return True if logging to stderr is enabled, false otherwise.
        [[nodiscard]] auto logToStderr() const noexcept -> bool;

        /// @brief Set the minimum log level.
        /// @param min_log_level The minimum log level to set.
        auto minLogLevel(int32_t min_log_level) noexcept -> void;

        /// @brief Set the log name.
        /// @param log_name The log name to set.
        auto logName(const std::string& log_name) -> void;

        /// @brief Enable or disable logging to stderr.
        /// @param log_to_stderr True to enable logging to stderr, false to disable.
        auto logToStderr(bool log_to_stderr) noexcept -> void;

        /// @brief Equality operator.
        /// @param other The other GLogParameters to compare with.
        /// @return True if both objects are equal, false otherwise.
        auto operator==(const GLogParameters& other) const noexcept -> bool;

        /// @brief Inequality operator.
        /// @param other The other GLogParameters to compare with.
        /// @return True if both objects are not equal, false otherwise.
        auto operator!=(const GLogParameters& other) const noexcept -> bool;

    private:
        int32_t min_log_level_{};
        std::string log_name_{};
        bool log_to_stderr_{};
    };

    inline GLogParameters::GLogParameters(const int32_t min_log_level, std::string log_name, const bool log_to_stderr)
        : min_log_level_(min_log_level), log_name_(std::move(log_name)), log_to_stderr_(log_to_stderr)
    {
    }

    inline auto GLogParameters::minLogLevel() const noexcept -> int32_t
    {
        return min_log_level_;
    }

    inline auto GLogParameters::logName() const noexcept -> std::string
    {
        return log_name_;
    }

    inline auto GLogParameters::logToStderr() const noexcept -> bool
    {
        return log_to_stderr_;
    }

    inline auto GLogParameters::minLogLevel(const int32_t min_log_level) noexcept -> void
    {
        min_log_level_ = min_log_level;
    }

    inline auto GLogParameters::logName(const std::string& log_name) -> void
    {
        log_name_ = log_name;
    }

    inline auto GLogParameters::logToStderr(const bool log_to_stderr) noexcept -> void
    {
        log_to_stderr_ = log_to_stderr;
    }

    inline auto GLogParameters::operator==(const GLogParameters& other) const noexcept -> bool
    {
        return min_log_level_ == other.min_log_level_ &&
               log_name_ == other.log_name_ &&
               log_to_stderr_ == other.log_to_stderr_;
    }

    inline auto GLogParameters::operator!=(const GLogParameters& other) const noexcept -> bool
    {
        return !(*this == other);
    }
} // namespace service

/// @brief YAML serialization specialization for GLogParameters.
/// Provides methods to encode and decode GLogParameters to/from YAML nodes.
template <>
struct YAML::convert<service::GLogParameters>
{
    /// @brief Decode a YAML node into a GLogParameters object.
    /// @param node The YAML node containing the configuration data.
    /// @param rhs The GLogParameters object to populate.
    /// @return True if decoding was successful.
    static auto decode(const Node& node, service::GLogParameters& rhs) -> bool
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

    /// @brief Encode a GLogParameters object into a YAML node.
    /// @param rhs The GLogParameters object to encode.
    /// @return A YAML node containing the configuration data.
    static auto encode(const service::GLogParameters& rhs) -> Node
    {
        Node node;
        node["minLogLevel"] = rhs.minLogLevel();
        node["logName"] = rhs.logName();
        node["logToStderr"] = rhs.logToStderr();
        return node;
    }
};
