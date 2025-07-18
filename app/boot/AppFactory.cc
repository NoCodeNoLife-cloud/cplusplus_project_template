#include "AppFactory.hpp"

#include <glog/logging.h>

#include "AppBoot.hpp"
#include "consoleApp/ConsoleExecutor.hpp"
#include "qtApp/QtExecutor.hpp"

namespace app
{
    auto AppFactory::registerAll() -> void
    {
        LOG(INFO) << "initializing the app launcher...";
        registerType<ConsoleExecutor>(coco::EnumUtil::getEnumClassName(AppType::ConsoleExecutor));
        registerType<QtExecutor>(coco::EnumUtil::getEnumClassName(AppType::QtExecutor));
    }
}
