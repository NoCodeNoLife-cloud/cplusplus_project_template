#pragma once
#include <string>

#include "config/ConfigPath.hpp"
#include "filesystem/serialize/YamlObjectSerializer.hpp"
#include "interface/IConfigurable.hpp"
#include "interface/IStartupTask.hpp"

namespace service
{
    class GLogConfigurator final : public IConfigurable, public IStartupTask
    {
    public:
        class GLogParameters final
        {
        public:
            [[nodiscard]] auto minLogLevel() const -> int32_t;
            [[nodiscard]] auto logName() const -> std::string;
            [[nodiscard]] auto logToStderr() const -> bool;
            auto minLogLevel(int32_t min_log_level) -> void;
            auto logName(const std::string& log_name) -> void;
            auto logToStderr(bool log_to_stderr) -> void;

        private:
            int32_t min_log_level_{};
            std::string log_name_{};
            bool log_to_stderr_{};
        };

        bool execute() override;

    private:
        const std::string GLogYAMLPath = ConfigPath::getConfigPath("glog_config.yaml");
        const GLogParameters config_ = common::YamlObjectSerializer<GLogParameters>::deserialize(GLogYAMLPath);

        [[nodiscard]] auto doConfig() -> bool override;
        static auto configLogToStdout(const GLogParameters& glog_options) -> void;
        static auto clean() -> void;
    };
}

template <>
struct YAML::convert<service::GLogConfigurator::GLogParameters>
{
    static auto decode(const Node& node, service::GLogConfigurator::GLogParameters& rhs) -> bool;
    static auto encode(const service::GLogConfigurator::GLogParameters& rhs) -> Node;
};
