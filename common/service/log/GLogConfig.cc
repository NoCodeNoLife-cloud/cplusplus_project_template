#include <filesystem/Directory.hpp>
#include <filesystem/serialize/YamlObjectSerializer.hpp>
#include <glog/logging.h>
#include <service/log/GLogConfig.hpp>
#include <service/log/GLogParameters.hpp>

namespace common
{
    auto GLogConfig::run() -> bool
    {
        if (!doConfig())
        {
            throw std::runtime_error("Failed to load config");
        }
        return true;
    }

    auto GLogConfig::doConfig() -> bool
    {
        const GLogParameters config = YamlObjectSerializer<GLogParameters>::deserialize("../common/service/log/glog_config.yaml");
        google::InitGoogleLogging(config.logName().c_str());
        FLAGS_minloglevel = config.minLogLevel();
        configLogToStdout(config);
        if (std::atexit(clean) != 0)
        {
            throw std::runtime_error("Failed to register cleanup function!");
        }
        return true;
    }

    auto GLogConfig::configLogToStdout(const GLogParameters& glog_options) -> void
    {
        FLAGS_logtostderr = glog_options.logToStderr();
    }

    auto GLogConfig::clean() -> void
    {
        google::ShutdownGoogleLogging();
    }
}
