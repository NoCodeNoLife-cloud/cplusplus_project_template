#pragma once
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>

namespace common::io
{
    class Date
    {
    public:
        Date();
        Date(int32_t year, int32_t month, int32_t day);
        Date(int32_t year, int32_t month, int32_t day, int32_t hours, int32_t minutes, int32_t seconds);
        explicit Date(int64_t timestamp);
        ~Date() = default;
        [[nodiscard]] auto clone() const -> Date;
        [[nodiscard]] auto equals(const Date& other) const -> bool;
        [[nodiscard]] auto after(const Date& other) const -> bool;
        [[nodiscard]] auto before(const Date& other) const -> bool;
        [[nodiscard]] auto getTime() const -> int64_t;
        [[nodiscard]] auto getYear() const -> int32_t;
        [[nodiscard]] auto getMonth() const -> int32_t;
        [[nodiscard]] auto getDay() const -> int32_t;
        [[nodiscard]] auto toString() const -> std::string;
        [[nodiscard]] auto hashCode() const -> size_t;
    private:
        std::chrono::system_clock::time_point time_point_;
        [[nodiscard]] auto toTm() const -> std::tm;
    };

    inline Date::Date(): time_point_(std::chrono::system_clock::now()) {}

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

    inline Date::Date(const int32_t year, const int32_t month, const int32_t day, const int32_t hours, const int32_t minutes, const int32_t seconds)
    {
        if (month < 1 || month > 12 || day < 1 || day > 31 || hours < 0 || hours > 23 || minutes < 0 || minutes > 59 || seconds < 0 || seconds > 59)
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

    inline Date::Date(const int64_t timestamp)
    {
        time_point_ = std::chrono::system_clock::time_point(std::chrono::milliseconds(timestamp));
    }

    inline auto Date::clone() const -> Date
    {
        return Date(getTime());
    }

    inline auto Date::equals(const Date& other) const -> bool
    {
        return time_point_ == other.time_point_;
    }

    inline auto Date::after(const Date& other) const -> bool
    {
        return time_point_ > other.time_point_;
    }

    inline auto Date::before(const Date& other) const -> bool
    {
        return time_point_ < other.time_point_;
    }

    inline auto Date::getTime() const -> int64_t
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

    inline auto Date::hashCode() const -> size_t
    {
        return std::hash<int64_t>()(getTime());
    }

    inline auto Date::toTm() const -> std::tm
    {
        const auto timeT = std::chrono::system_clock::to_time_t(time_point_);
        std::tm tm = {};
        localtime_s(&tm, &timeT);
        return tm;
    }
}
