#pragma once
#include <string>

#include "src/GLogParameters.hpp"

namespace glog
{
    /// @brief Configures Google Logging (glog) library with specified parameters
    /// @details This class handles the initialization and configuration of the glog library
    /// based on the provided configuration parameters
    class GLogConfigurator final
    {
    public:
        /// @brief Constructor with YAML configuration file path
        /// @param glog_yaml_path Path to the YAML configuration file
        explicit GLogConfigurator(std::string glog_yaml_path);

        /// @brief Execute the configuration process
        /// @return True if configuration was successful
        /// @throws std::runtime_error If configuration fails
        [[nodiscard]] auto execute() const
            -> bool;

        /// @brief Get the current configuration parameters
        /// @return A const reference to the GLogParameters object
        [[nodiscard]] auto getConfig() const noexcept
            -> const GLogParameters&;

        /// @brief Update the configuration parameters
        /// @param config The new configuration parameters
        auto updateConfig(const GLogParameters& config)
            -> void;

    private:
        /// @brief Perform the actual glog configuration
        /// @return True if configuration was successful
        [[nodiscard]] auto doConfig() const
            -> bool;

        /// @brief Clean up glog resources
        static auto clean() noexcept
            -> void;

        std::string glog_yaml_path_;
        GLogParameters config_;
    };
}