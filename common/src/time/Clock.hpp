#pragma once
#include <chrono>
#include <string>

namespace common
{
    /// @brief Utility class for time-related operations
    class Clock
    {
    public:
        Clock() = delete;

        /// @brief Get current date and time as a string in format "YYYY-MM-DD HH:MM:SS"
        /// @return Formatted date and time string
        [[nodiscard]] static auto getCurrentDateTimeString() noexcept -> std::string;

        /// @brief Get current date and time as a compressed string in format "YYYYMMDD_HHMMSS"
        /// @return Compressed date and time string
        [[nodiscard]] static auto getCompressedCurrentDateTimeString() noexcept -> std::string;
    };
}
