#pragma once
#include <string>

#include "GLogParameters.hpp"
#include "include/service/interface/IConfigurable.hpp"
#include "include/service/interface/IStartupTask.hpp"

namespace service
{
    /// @brief Configurator class for Google Logging (log) library.
    /// This class handles the configuration and initialization of the log logging system
    /// by reading parameters from a YAML configuration file and setting up the appropriate
    /// logging options.
    class GLogConfigurator final : public IConfigurable, public IStartupTask
    {
    public:
        /// @brief Constructor with YAML configuration file path.
        /// @param GLogYAMLPath Path to the YAML configuration file.
        explicit GLogConfigurator(std::string GLogYAMLPath);

        /// @brief Execute the startup task.
        /// @return True if the task was executed successfully, false otherwise.
        auto execute() -> bool override;

        /// @brief Get the configuration parameters.
        /// @return The configuration parameters.
        [[nodiscard]] auto getConfig() const noexcept -> const GLogParameters&;

        /// @brief Update the configuration parameters.
        /// @param config The new configuration parameters.
        auto updateConfig(const GLogParameters& config) -> void;

    private:
        std::string GLogYAMLPath_{};
        GLogParameters config_{};

        /// @brief Perform the configuration.
        /// @return True if the configuration was successful, false otherwise.
        [[nodiscard]] auto doConfig() -> bool override;

        /// @brief Configure logging to stdout based on the provided options.
        /// @param glog_options The logging options to use for configuration.
        static auto configLogToStdout(const GLogParameters& glog_options) noexcept -> void;

        /// @brief Clean up any resources used by the configurator.
        static auto clean() noexcept -> void;
    };
} // namespace service
