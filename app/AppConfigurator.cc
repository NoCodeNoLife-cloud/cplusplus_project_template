#include <AppConfigurator.hpp>
#include <glog/logging.h>

namespace app
{
    auto AppConfigurator::run() -> bool
    {
        if (!doConfig())
        {
            throw std::runtime_error("Configuration program failed");
        }
        return true;
    }

    auto AppConfigurator::doConfig() -> bool
    {
        LOG(INFO) << "Configuring application...";
        return true;
    }
}
