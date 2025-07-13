#include "AppFactory.hpp"

#include <glog/logging.h>

#include "AppBoot.hpp"
#include "consoleApp/ConsoleExecutor.hpp"
#include "qtApp/QtExecutor.hpp"

namespace app
{
    auto AppFactory::registerAll() -> void
    {
        LOG(INFO) << "Initializing the app launcher...";
        registerType<ConsoleExecutor>(AppBoot::APP_MAP.at("console"));
        registerType<QtExecutor>(AppBoot::APP_MAP.at("qt"));
    }
}
