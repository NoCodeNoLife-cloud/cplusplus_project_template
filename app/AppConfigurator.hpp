#pragma once
#include <AppParameters.hpp>
#include <string>
#include <filesystem/serialize/YamlObjectSerializer.hpp>
#include <interface/IStartupTask.hpp>
#include <service/IConfigurable.hpp>

namespace app
{
    class AppConfigurator final : public coco::IConfigurable, public IStartupTask
    {
    public:
        auto run() -> bool override;

    private:
        const std::string appYAMLPath = "../app/app_config.yaml";
        const AppParameters config_ = coco::YamlObjectSerializer<AppParameters>::deserialize(appYAMLPath);

        [[nodiscard]] auto doConfig() -> bool override;
    };
}
