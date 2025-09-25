#pragma once
#include <chrono>
#include <string>
#include <format>
#include <cstdint>

namespace fox
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

    inline auto Clock::getCurrentDateTimeString() noexcept -> std::string
    {
        const auto now = std::chrono::system_clock::now();
        const auto local_time = std::chrono::current_zone()->to_local(now);
        const auto date = std::chrono::floor<std::chrono::days>(local_time);
        const std::chrono::year_month_day ymd{date};
        const std::chrono::hh_mm_ss time_part{local_time - date};
        return std::format("{0:04d}-{1:02d}-{2:02d} {3:02d}:{4:02d}:{5:02d}", static_cast<int32_t>(ymd.year()),
                           static_cast<unsigned>(ymd.month()), static_cast<unsigned>(ymd.day()),
                           time_part.hours().count(), time_part.minutes().count(), time_part.seconds().count());
    }

    inline auto Clock::getCompressedCurrentDateTimeString() noexcept -> std::string
    {
        const auto now = std::chrono::system_clock::now();
        const auto local_time = std::chrono::current_zone()->to_local(now);
        const auto date = std::chrono::floor<std::chrono::days>(local_time);
        const std::chrono::year_month_day ymd{date};
        const std::chrono::hh_mm_ss time_part{local_time - date};
        return std::format("{0:04d}{1:02d}{2:02d}_{3:02d}{4:02d}{5:02d}", static_cast<int32_t>(ymd.year()),
                           static_cast<unsigned>(ymd.month()), static_cast<unsigned>(ymd.day()),
                           time_part.hours().count(), time_part.minutes().count(), time_part.seconds().count());
    }
}
