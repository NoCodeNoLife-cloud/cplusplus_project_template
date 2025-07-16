#pragma once
#include <cstdint>
#include <string>

#include "AppParameters.hpp"
#include "filesystem/serialize/YamlObjectSerializer.hpp"

namespace app
{
    class AppBoot final
    {
    public:
        auto boot(int32_t argc, char* argv[]) const -> bool;

    private:
        const std::string appYAMLPath = "../../app/boot/app_config.yaml";
        const AppParameters config_ = coco::YamlObjectSerializer<AppParameters>::deserialize(appYAMLPath);
    };
}
