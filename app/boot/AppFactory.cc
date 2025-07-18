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
        registerType<ConsoleExecutor>(static_cast<std::string>(magic_enum::enum_name(AppType::ConsoleExecutor)));
        registerType<QtExecutor>(static_cast<std::string>(magic_enum::enum_name(AppType::QtExecutor)));
    }
}
