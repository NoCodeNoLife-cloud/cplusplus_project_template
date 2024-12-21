#pragma once
#include <string>


namespace service
{
    class ConfigPath
    {
    public:
        [[nodiscard]] static auto getConfigPath(const std::string& config_name) -> std::string;

    private:
        static inline std::string CONFIG_DIR = "../../service/config/";
    };
}
