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
        ~Date() = default;

        Date(): time_point_(std::chrono::system_clock::now())
        {
        }

        Date(const int year, const int month, const int day)
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

        Date(const int year, const int month, const int day, const int hours, const int minutes, const int seconds)
        {
            if (month < 1 || month > 12 || day < 1 || day > 31 || hours < 0 || hours > 23 || minutes < 0 || minutes > 59
                || seconds < 0 || seconds > 59)
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

        explicit Date(const long long timestamp)
        {
            time_point_ = std::chrono::system_clock::time_point(std::chrono::milliseconds(timestamp));
        }

        [[nodiscard]] auto clone() const -> Date
        {
            return Date(getTime());
        }

        [[nodiscard]] auto equals(const Date& other) const -> bool
        {
            return time_point_ == other.time_point_;
        }

        [[nodiscard]] auto after(const Date& other) const -> bool
        {
            return time_point_ > other.time_point_;
        }

        [[nodiscard]] auto before(const Date& other) const -> bool
        {
            return time_point_ < other.time_point_;
        }

        [[nodiscard]] auto getTime() const -> long long
        {
            return std::chrono::duration_cast<std::chrono::milliseconds>(time_point_.time_since_epoch()).count();
        }

        [[nodiscard]] auto getYear() const -> int
        {
            return toTm().tm_year + 1900;
        }

        [[nodiscard]] auto getMonth() const -> int
        {
            return toTm().tm_mon + 1;
        }

        [[nodiscard]] auto getDay() const -> int
        {
            return toTm().tm_mday;
        }

        [[nodiscard]] auto toString() const -> std::string
        {
            const auto tm = toTm();
            std::ostringstream oss;
            oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
            return oss.str();
        }

        [[nodiscard]] auto hashCode() const -> size_t
        {
            return std::hash<long long>()(getTime());
        }

    private:
        std::chrono::system_clock::time_point time_point_;

        [[nodiscard]] auto toTm() const -> std::tm
        {
            const auto timeT = std::chrono::system_clock::to_time_t(time_point_);
            std::tm tm = {};
            localtime_s(&tm, &timeT);
            return tm;
        }
    };
}
