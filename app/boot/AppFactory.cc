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
        registerType<ConsoleExecutor>(TYPE.at("console"));
        registerType<QtExecutor>(TYPE.at("qt"));
    }
}
