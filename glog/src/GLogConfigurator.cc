#include "include/GLogConfigurator.hpp"

#include <glog/logging.h>

namespace service
{
    GLogConfigurator::GLogConfigurator(std::string GLogYAMLPath) : GLogYAMLPath_(std::move(GLogYAMLPath))
    {
        config_.deserializedFromYamlFile(GLogYAMLPath_);
    }

    auto GLogConfigurator::execute() -> bool
    {
        if (!doConfig())
        {
            throw std::runtime_error("Configuration GLog failed");
        }
        return true;
    }

    auto GLogConfigurator::getConfig() const noexcept -> const GLogParameters&
    {
        return config_;
    }

    auto GLogConfigurator::updateConfig(const GLogParameters& config) -> void
    {
        config_ = config;
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
        LOG(INFO) << "configuring glog...";
        return true;
    }

    auto GLogConfigurator::configLogToStdout(const GLogParameters& glog_options) noexcept -> void
    {
        FLAGS_logtostderr = glog_options.logToStderr();
    }

    auto GLogConfigurator::clean() noexcept -> void
    {
        google::ShutdownGoogleLogging();
    }
} // namespace service
