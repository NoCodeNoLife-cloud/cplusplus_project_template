#include "AppBoot.hpp"

#include "AppFactory.hpp"

namespace app
{
    auto AppBoot::boot(const int32_t argc, char* argv[]) const -> bool
    {
        return AppFactory::createObject(APP_MAP.at(config_.appType()))->execute(argc, argv);
    }
}
