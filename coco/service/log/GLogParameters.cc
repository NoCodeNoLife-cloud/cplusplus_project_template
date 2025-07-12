#include <service/log/GLogParameters.hpp>

namespace coco
{
    GLogParameters::GLogParameters() = default;
    GLogParameters::~GLogParameters() = default;
    GLogParameters::GLogParameters(const GLogParameters& other) = default;
    GLogParameters& GLogParameters::operator=(const GLogParameters& other) = default;
    GLogParameters::GLogParameters(GLogParameters&& other) noexcept = default;

    auto GLogParameters::minLogLevel() const -> int32_t
    {
        return min_log_level_;
    }

    auto GLogParameters::logName() const -> std::string
    {
        return log_name_;
    }

    auto GLogParameters::logToStderr() const -> bool
    {
        return log_to_stderr_;
    }

    auto GLogParameters::minLogLevel(const int32_t min_log_level) -> void
    {
        min_log_level_ = min_log_level;
    }

    auto GLogParameters::logName(const std::string& log_name) -> void
    {
        log_name_ = log_name;
    }

    auto GLogParameters::logToStderr(const bool log_to_stderr) -> void
    {
        log_to_stderr_ = log_to_stderr;
    }
}
