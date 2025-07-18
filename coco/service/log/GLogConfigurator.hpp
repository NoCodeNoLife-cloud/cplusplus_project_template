#pragma once
#include <string>

#include "filesystem/serialize/YamlObjectSerializer.hpp"
#include "interface/IStartupTask.hpp"
#include "service/IConfigurable.hpp"

namespace coco
{
    class GLogConfigurator final : public IConfigurable, public app::IStartupTask
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
        const std::string GLogYAMLPath = "../../coco/service/log/glog_config.yaml";
        const GLogParameters config_ = YamlObjectSerializer<GLogParameters>::deserialize(GLogYAMLPath);

        [[nodiscard]] auto doConfig() -> bool override;
        static auto configLogToStdout(const GLogParameters& glog_options) -> void;
        static auto clean() -> void;
    };
}

template <>
struct YAML::convert<coco::GLogConfigurator::GLogParameters>
{
    static auto decode(const Node& node, coco::GLogConfigurator::GLogParameters& rhs) -> bool;
    static auto encode(const coco::GLogConfigurator::GLogParameters& rhs) -> Node;
};
