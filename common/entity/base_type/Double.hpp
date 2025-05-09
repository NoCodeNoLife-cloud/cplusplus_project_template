#pragma once
#include <string>
#include <entity/base_type/Object.hpp>

namespace common {
  class Double final : public Object {
  public:
    static constexpr double POSITIVE_INFINITY = std::numeric_limits<double>::infinity();
    static constexpr double NEGATIVE_INFINITY = -std::numeric_limits<double>::infinity();
    static constexpr double NaN = std::numeric_limits<double>::quiet_NaN();
    static constexpr double MAX_VALUE = std::numeric_limits<double>::max();
    static constexpr double MIN_VALUE = std::numeric_limits<double>::min();
    explicit Double(double value);
    ~Double() override;
    explicit operator double() const;
    [[nodiscard]] auto doubleValue() const -> double;
    static auto parseDouble(const std::string& str) -> Double;
    auto operator<=>(const Double& other) const -> std::partial_ordering;
    auto operator+(const Double& other) const -> Double;
    auto operator-(const Double& other) const -> Double;
    auto operator*(const Double& other) const -> Double;
    auto operator/(const Double& other) const -> Double;

  private:
    double value_{0.0};
  };
}
