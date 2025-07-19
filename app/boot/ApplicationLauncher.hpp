#pragma once
#include <cstdint>
#include <string>

#include "config/AppParameters.hpp"
#include "filesystem/serialize/YamlObjectSerializer.hpp"

namespace app
{
    class ApplicationLauncher final
    {
    public:
        auto boot(int32_t argc, char* argv[]) const -> bool;

    private:
        const std::string appYAMLPath = "../../app/boot/config/app_config.yaml";
        const AppParameters config_ = coco::YamlObjectSerializer<AppParameters>::deserialize(appYAMLPath);
    };
}
