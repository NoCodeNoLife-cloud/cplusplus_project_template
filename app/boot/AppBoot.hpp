#pragma once
#include <string>
#include <filesystem/serialize/YamlObjectSerializer.hpp>
#include <boot/AppParameters.hpp>

namespace app
{
    class AppBoot final
    {
    public:
        auto boot(int32_t argc, char* argv[]) const -> bool;

    private:
        const std::string appYAMLPath = "../app/boot/app_config.yaml";
        const AppParameters config_ = coco::YamlObjectSerializer<AppParameters>::deserialize(appYAMLPath);
    };
}
