#pragma once
#include <string>

#include "Object.hpp"

namespace common
{
    class Double final : public Object
    {
    public:
        static constexpr double POSITIVE_INFINITY = std::numeric_limits<double>::infinity();
        static constexpr double NEGATIVE_INFINITY = -std::numeric_limits<double>::infinity();
        static constexpr double NaN = std::numeric_limits<double>::quiet_NaN();
        static constexpr double MAX_VALUE = std::numeric_limits<double>::max();
        static constexpr double MIN_VALUE = std::numeric_limits<double>::min();
        explicit Double(double value = 0.0);
        ~Double() override;
        Double(const Double& other);
        Double(Double&& other) noexcept;
        Double& operator=(const Double& other);
        Double& operator=(Double&& other) noexcept;
        explicit operator double() const;
        [[nodiscard]] auto hashCode() const -> size_t override;
        [[nodiscard]] auto toString() const -> std::string override;
        [[nodiscard]] auto doubleValue() const -> double;
        static auto parseDouble(const std::string& str) -> Double;
        auto operator<=>(const Double& other) const -> std::partial_ordering;
        auto operator==(const Double& other) const -> bool;
        auto operator+(const Double& other) const -> Double;
        auto operator-(const Double& other) const -> Double;
        auto operator*(const Double& other) const -> Double;
        auto operator/(const Double& other) const -> Double;

    private:
        friend std::formatter<Double>;
        double value_{0.0};
    };
}

template <>
struct std::formatter<common::Double> : common::GenericFormatter<common::Double, &common::Double::value_>
{
};
