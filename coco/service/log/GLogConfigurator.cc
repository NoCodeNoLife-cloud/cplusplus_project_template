#include <filesystem/Directory.hpp>
#include <glog/logging.h>
#include <service/log/GLogConfigurator.hpp>
#include <service/log/GLogParameters.hpp>

namespace coco
{
    auto GLogConfigurator::run() -> bool
    {
        if (!doConfig())
        {
            throw std::runtime_error("Configuration GLog failed");
        }
        return true;
    }

    auto GLogConfigurator::doConfig() -> bool
    {
        google::InitGoogleLogging(config_.logName().c_str());
        FLAGS_minloglevel = config_.minLogLevel();
        configLogToStdout(config_);
        if (std::atexit(clean) != 0)
        {
            throw std::runtime_error("Failed to register cleanup function!");
        }
        LOG(INFO) << "Configuring glog...";
        return true;
    }

    auto GLogConfigurator::configLogToStdout(const GLogParameters& glog_options) -> void
    {
        FLAGS_logtostderr = glog_options.logToStderr();
    }

    auto GLogConfigurator::clean() -> void
    {
        google::ShutdownGoogleLogging();
    }
}
