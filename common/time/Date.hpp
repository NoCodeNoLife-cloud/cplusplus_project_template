#pragma once
#include <chrono>
#include <string>

namespace common
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
}
