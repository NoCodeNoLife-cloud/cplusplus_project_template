#pragma once
#include <chrono>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>
#include <cstdint>
#include <functional>

namespace fox
{
    /// @brief A class representing a specific instant in time, with millisecond precision.
    /// The Date class represents a specific point in time, measured in milliseconds
    /// since the Unix epoch (January 1, 1970, 00:00:00 GMT). It provides methods
    /// for creating, manipulating, and comparing dates, as well as converting
    /// between different date representations.
    class Date
    {
    public:
        Date() noexcept;

        Date(int32_t year, int32_t month, int32_t day);

        Date(int32_t year, int32_t month, int32_t day, int32_t hours, int32_t minutes,
             int32_t seconds);

        explicit Date(int64_t timestamp) noexcept;

        ~Date();

        /// @brief Creates and returns a copy of this object.
        [[nodiscard]] auto clone() const -> Date;

        /// @brief Compares this date to the specified date.
        [[nodiscard]] auto equals(const Date& other) const noexcept -> bool;

        /// @brief Tests if this date is after the specified date.
        [[nodiscard]] auto after(const Date& other) const noexcept -> bool;

        /// @brief Tests if this date is before the specified date.
        [[nodiscard]] auto before(const Date& other) const noexcept -> bool;

        /// @brief Returns the number of milliseconds since January 1, 1970, 00:00:00 GMT.
        [[nodiscard]] auto getTime() const noexcept -> int64_t;

        /// @brief Returns the year represented by this date.
        [[nodiscard]] auto getYear() const -> int32_t;

        /// @brief Returns the month represented by this date.
        [[nodiscard]] auto getMonth() const -> int32_t;

        /// @brief Returns the day of the month represented by this date.
        [[nodiscard]] auto getDay() const -> int32_t;

        /// @brief Converts this date to a string representation.
        [[nodiscard]] auto toString() const -> std::string;

        /// @brief Returns a hash code value for this date.
        [[nodiscard]] auto hashCode() const noexcept -> size_t;

    private:
        std::chrono::system_clock::time_point time_point_;

        /// @brief Converts the time point to a std::tm structure.
        [[nodiscard]] auto toTm() const -> std::tm;
    };

    inline Date::Date() noexcept : time_point_(std::chrono::system_clock::now())
    {
    }

    inline Date::Date(const int32_t year, const int32_t month, const int32_t day)
    {
        if (month < 1 || month > 12 || day < 1 || day > 31)
        {
            throw std::invalid_argument("Invalid date components.");
        }
        std::tm tm = {};
        tm.tm_year = year - 1900;
        tm.tm_mon = month - 1;
        tm.tm_mday = day;
        time_point_ = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    }

    inline Date::Date(const int32_t year, const int32_t month, const int32_t day, const int32_t hours,
                      const int32_t minutes, const int32_t seconds)
    {
        if (month < 1 || month > 12 || day < 1 || day > 31 || hours < 0 || hours > 23 || minutes < 0 || minutes > 59
            ||
            seconds < 0 || seconds > 59)
        {
            throw std::invalid_argument("Invalid date-time components.");
        }
        std::tm tm = {};
        tm.tm_year = year - 1900;
        tm.tm_mon = month - 1;
        tm.tm_mday = day;
        tm.tm_hour = hours;
        tm.tm_min = minutes;
        tm.tm_sec = seconds;
        time_point_ = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    }

    inline Date::Date(const int64_t timestamp) noexcept
    {
        time_point_ = std::chrono::system_clock::time_point(std::chrono::milliseconds(timestamp));
    }

    inline Date::~Date() = default;

    inline auto Date::clone() const -> Date
    {
        return Date(getTime());
    }

    inline auto Date::equals(const Date& other) const noexcept -> bool
    {
        return time_point_ == other.time_point_;
    }

    inline auto Date::after(const Date& other) const noexcept -> bool
    {
        return time_point_ > other.time_point_;
    }

    inline auto Date::before(const Date& other) const noexcept -> bool
    {
        return time_point_ < other.time_point_;
    }

    inline auto Date::getTime() const noexcept -> int64_t
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(time_point_.time_since_epoch()).count();
    }

    inline auto Date::getYear() const -> int32_t
    {
        return toTm().tm_year + 1900;
    }

    inline auto Date::getMonth() const -> int32_t
    {
        return toTm().tm_mon + 1;
    }

    inline auto Date::getDay() const -> int32_t
    {
        return toTm().tm_mday;
    }

    inline auto Date::toString() const -> std::string
    {
        const auto tm = toTm();
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    inline auto Date::hashCode() const noexcept -> size_t
    {
        return std::hash<int64_t>{}(getTime());
    }

    inline auto Date::toTm() const -> std::tm
    {
        const auto timeT = std::chrono::system_clock::to_time_t(time_point_);
        std::tm tm = {};
#ifdef _WIN32
        localtime_s(&tm, &timeT);
#else
        localtime_r(&timeT, &tm);
#endif
        return tm;
    }
} // namespace fox
