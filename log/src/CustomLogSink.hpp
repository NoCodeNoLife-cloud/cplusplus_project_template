#pragma once
#include <thread>

#include <glog/logging.h>

namespace glog
{
    /// @brief Custom log sink implementation for Google Logging (glog)
    /// @details This class implements a custom log sink that formats log messages
    /// with timestamp, thread ID, source location, and log level
    class CustomLogSink final : public google::LogSink
    {
    public:
        /// @brief Send log message to custom sink
        /// @param severity Log severity level
        /// @param full_filename Full path to source file
        /// @param base_filename Base name of source file
        /// @param line Line number in source file
        /// @param log_message_time Time of log entry
        /// @param message Log message content
        /// @param message_len Length of log message
        auto send(google::LogSeverity severity,
                  const char* full_filename,
                  const char* base_filename,
                  int line,
                  const google::LogMessageTime& log_message_time,
                  const char* message,
                  size_t message_len) noexcept
            -> void override;

    private:
        /// @brief Get the log level prefix string
        /// @param severity Log severity level
        /// @return String representation of the log level
        [[nodiscard]] static auto getLogLevelPrefix(google::LogSeverity severity) noexcept
            -> const char*;
    };
} // namespace glog