#include "ApplicationLauncher.hpp"

#include <glog/logging.h>

#include "AppFactory.hpp"

namespace app
{
    auto ApplicationLauncher::boot(const int32_t argc, char* argv[]) const -> bool
    {
        LOG(INFO) << "boot app...";
        return AppFactory::createObject(AppFactory::TYPE.at(config_.appType()))->execute(argc, argv);
    }
}
