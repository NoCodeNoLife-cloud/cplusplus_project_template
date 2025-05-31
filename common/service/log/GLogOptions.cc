#include "GLogOptions.hpp"

namespace common
{
    GLogOptions::GLogOptions() = default;
    GLogOptions::~GLogOptions() = default;
    GLogOptions::GLogOptions(const GLogOptions& other) = default;
    GLogOptions& GLogOptions::operator=(const GLogOptions& other) = default;
    GLogOptions::GLogOptions(GLogOptions&& other) noexcept = default;

    auto GLogOptions::minLogLevel() const -> int32_t
    {
        return min_log_level_;
    }

    auto GLogOptions::logName() const -> std::string
    {
        return log_name_;
    }

    auto GLogOptions::logToStderr() const -> bool
    {
        return log_to_stderr_;
    }

    auto GLogOptions::minLogLevel(const int32_t min_log_level) -> void
    {
        min_log_level_ = min_log_level;
    }

    auto GLogOptions::logName(const std::string& log_name) -> void
    {
        log_name_ = log_name;
    }

    auto GLogOptions::logToStderr(bool log_to_stderr) -> void
    {
        log_to_stderr_ = log_to_stderr;
    }
}
