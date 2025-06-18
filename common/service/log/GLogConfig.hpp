#pragma once
#include <interface/IStartupTask.hpp>
#include <service/IConfigurable.hpp>
#include <service/log/GLogParameters.hpp>

namespace common
{
    class GLogConfig final : public IConfigurable, public app::IStartupTask
    {
    public:
        bool run() override;

    private:
        [[nodiscard]] auto doConfig() -> bool override;
        static auto configLogToStdout(const GLogParameters& glog_options) -> void;
        static auto clean() -> void;
    };
}
