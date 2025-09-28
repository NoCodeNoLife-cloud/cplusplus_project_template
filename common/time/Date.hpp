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
    /// The class represents a specific point in time, measured in milliseconds
    /// since the Unix epoch (January 1, 1970, 00:00:00 GMT). It provides methods
    /// for creating, manipulating, and comparing dates, as well as converting
    /// between different date representations.
    class Date
    {
    public:
        /// @brief Default constructor, initializes to current time
        Date() noexcept;

        /// @brief Construct a date with year, month, and day
        /// @param year The year (e.g., 2023)
        /// @param month The month (1-12)
        /// @param day The day of the month (1-31)
        /// @throws std::invalid_argument If date components are invalid
        Date(int32_t year, int32_t month, int32_t day);

        /// @brief Construct a date with year, month, day, hours, minutes, and seconds
        /// @param year The year (e.g., 2023)
        /// @param month The month (1-12)
        /// @param day The day of the month (1-31)
        /// @param hours The hours (0-23)
        /// @param minutes The minutes (0-59)
        /// @param seconds The seconds (0-59)
        /// @throws std::invalid_argument If date-time components are invalid
        Date(int32_t year, int32_t month, int32_t day, int32_t hours, int32_t minutes,
             int32_t seconds);

        /// @brief Construct a date from a timestamp
        /// @param timestamp Milliseconds since Unix epoch
        explicit Date(int64_t timestamp) noexcept;

        /// @brief Destructor
        ~Date();

        /// @brief Creates and returns a copy of this object.
        /// @return A copy of this date
        [[nodiscard]] auto clone() const -> Date;

        /// @brief Compares this date to the specified date.
        /// @param other The date to compare with
        /// @return true if the dates are equal, false otherwise
        [[nodiscard]] auto equals(const Date& other) const noexcept -> bool;

        /// @brief Tests if this date is after the specified date.
        /// @param other The date to compare with
        /// @return true if this date is after the other date, false otherwise
        [[nodiscard]] auto after(const Date& other) const noexcept -> bool;

        /// @brief Tests if this date is before the specified date.
        /// @param other The date to compare with
        /// @return true if this date is before the other date, false otherwise
        [[nodiscard]] auto before(const Date& other) const noexcept -> bool;

        /// @brief Returns the number of milliseconds since January 1, 1970, 00:00:00 GMT.
        /// @return The timestamp in milliseconds
        [[nodiscard]] auto getTime() const noexcept -> int64_t;

        /// @brief Returns the year represented by this date.
        /// @return The year (e.g., 2023)
        [[nodiscard]] auto getYear() const -> int32_t;

        /// @brief Returns the month represented by this date.
        /// @return The month (1-12)
        [[nodiscard]] auto getMonth() const -> int32_t;

        /// @brief Returns the day of the month represented by this date.
        /// @return The day of the month (1-31)
        [[nodiscard]] auto getDay() const -> int32_t;

        /// @brief Converts this date to a string representation.
        /// @return A string representation of the date in format "YYYY-MM-DD HH:MM:SS"
        [[nodiscard]] auto toString() const -> std::string;

        /// @brief Returns a hash code value for this date.
        /// @return The hash code value
        [[nodiscard]] auto hashCode() const noexcept -> size_t;

    private:
        std::chrono::system_clock::time_point time_point_{};

        /// @brief Converts the time point to a std::tm structure.
        /// @return The tm structure representation of the date
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
        tm.tm_hour = 0;
        tm.tm_min = 0;
        tm.tm_sec = 0;
        tm.tm_isdst = -1; // Let mktime determine if DST is in effect
        const auto timeT = std::mktime(&tm);
        if (timeT == -1)
        {
            throw std::invalid_argument("Invalid date components.");
        }
        time_point_ = std::chrono::system_clock::from_time_t(timeT);
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
        tm.tm_isdst = -1; // Let mktime determine if DST is in effect
        const auto timeT = std::mktime(&tm);
        if (timeT == -1)
        {
            throw std::invalid_argument("Invalid date-time components.");
        }
        time_point_ = std::chrono::system_clock::from_time_t(timeT);
    }

    inline Date::Date(const int64_t timestamp) noexcept : time_point_(std::chrono::milliseconds(timestamp))
    {
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
}
