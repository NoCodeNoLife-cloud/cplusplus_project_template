#include "AppFactory.hpp"

#include <glog/logging.h>

#include "ApplicationLauncher.hpp"
#include "consoleApp/ConsoleExecutor.hpp"
#include "qtApp/QtExecutor.hpp"

namespace app
{
    auto AppFactory::registerAll() -> void
    {
        LOG(INFO) << "initializing the app launcher...";
        registerType<ConsoleExecutor>(CONSOLE_EXECUTOR_NAME);
        registerType<QtExecutor>(QT_EXECUTOR_NAME);
    }
}
