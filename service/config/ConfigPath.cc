#include "ConfigPath.hpp"


namespace service
{
    auto ConfigPath::getConfigPath(const std::string& config_name) -> std::string
    {
        return CONFIG_DIR + config_name;
    }
}
