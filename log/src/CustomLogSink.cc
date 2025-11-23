#include "CustomLogSink.hpp"

#include <iomanip>
#include <iosfwd>
#include <iostream>
#include <sstream>
#include <thread>

#include "GLogConfigurator.hpp"

namespace glog
{
    /// @brief Send log message to custom sink
    /// @param severity Log severity level
    /// @param full_filename Full path to source file
    /// @param base_filename Base name of source file
    /// @param line Line number in source file
    /// @param log_message_time Time of log entry
    /// @param message Log message content
    /// @param message_len Length of log message
    auto CustomLogSink::send(const google::LogSeverity severity,
                             const char* full_filename,
                             const char* base_filename,
                             const int line,
                             const google::LogMessageTime& log_message_time,
                             const char* message,
                             const size_t message_len) noexcept
        -> void
    {
        try
        {
            // Format: Year/Month/Day 12-hour time Thread ID Code location Log content
            std::ostringstream oss;

            // Get time structure from LogMessageTime
            const auto time_tm = log_message_time.tm();

            // Date in Year/Month/Day format
            oss << std::put_time(&time_tm, "%Y/%m/%d ");

            // 12-hour time format with AM/PM
            oss << std::put_time(&time_tm, "%I:%M:%S %p ");

            // Thread ID
            oss << "T:" << std::this_thread::get_id() << " ";

            // Code location
            oss << base_filename << ":" << line << " ";

            // Log level prefix
            oss << getLogLevelPrefix(severity) << " ";

            // Log message
            oss.write(message, static_cast<std::streamsize>(message_len));

            // Output to stderr
            std::cerr << oss.str() << std::endl;
        }
        catch (...)
        {
            // Silently ignore exceptions in logging to prevent crashes
        }
    }

    /// @brief Get the log level prefix string
    /// @param severity Log severity level
    /// @return String representation of the log level
    [[nodiscard]] auto CustomLogSink::getLogLevelPrefix(const google::LogSeverity severity) noexcept
        -> const char*
    {
        switch (severity)
        {
        case google::GLOG_INFO:
            return "INFO";
        case google::GLOG_WARNING:
            return "WARNING";
        case google::GLOG_ERROR:
            return "ERROR";
        case google::GLOG_FATAL:
            return "FATAL";
        default:
            return "UNKNOWN";
        }
    }
} // namespace glog
