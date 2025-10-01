#include "src/GLogConfigurator.hpp"

#include <glog/logging.h>
#include <iostream>
#include <thread>

#include "CustomLogSink.hpp"

namespace glog
{
    // Static variable to hold the custom log sink for cleanup
    static std::unique_ptr<google::LogSink> static_custom_log_sink_;

    GLogConfigurator::GLogConfigurator(std::string glog_yaml_path) : glog_yaml_path_(std::move(glog_yaml_path))
    {
        config_.deserializedFromYamlFile(glog_yaml_path_);
    }

    auto GLogConfigurator::execute() const -> bool
    {
        // ReSharper disable once CppDFAConstantConditions
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

    auto GLogConfigurator::doConfig() const -> bool
    {
        google::InitGoogleLogging(config_.logName().c_str());
        FLAGS_minloglevel = config_.minLogLevel();
        configLogToStdout(config_);

        // Apply custom log format if enabled
        if (config_.customLogFormat()) {
            static_custom_log_sink_ = std::make_unique<CustomLogSink>();
            google::AddLogSink(static_custom_log_sink_.get());
            // Disable default logging to avoid duplicate messages and file creation
            FLAGS_logtostderr = false;
            FLAGS_alsologtostderr = false;
            FLAGS_log_dir = ""; // Ensure no log files are created
        } else {
            // When not using custom format, ensure proper stderr logging and prevent file creation
            FLAGS_logtostderr = config_.logToStderr();
            FLAGS_alsologtostderr = false;
            FLAGS_log_dir = "";
        }

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
        if (static_custom_log_sink_) {
            google::RemoveLogSink(static_custom_log_sink_.get());
            static_custom_log_sink_.reset();
        }
        google::ShutdownGoogleLogging();
    }
}
