#pragma once
#include <string>

#include "GLogParameters.hpp"
#include "filesystem/serialize/YamlObjectSerializer.hpp"
#include "interface/IStartupTask.hpp"
#include "service/IConfigurable.hpp"


namespace coco
{
    class GLogConfigurator final : public IConfigurable, public app::IStartupTask
    {
    public:
        bool run() override;

    private:
        const std::string GLogYAMLPath = "../../coco/service/log/glog_config.yaml";
        const GLogParameters config_ = YamlObjectSerializer<GLogParameters>::deserialize(GLogYAMLPath);

        [[nodiscard]] auto doConfig() -> bool override;
        static auto configLogToStdout(const GLogParameters& glog_options) -> void;
        static auto clean() -> void;
    };
}
