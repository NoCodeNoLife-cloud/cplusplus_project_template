#pragma once
#include <cmath>
#include <format>
#include <limits>
#include <numbers>
#include <random>

namespace common::math
{
    class MathUtil abstract
    {
    public:
        static auto abs(double a) -> double;
        static auto abs(float a) -> float;
        static auto abs(int32_t a) -> int32_t;
        static auto abs(int64_t a) -> int64_t;
        static auto acos(double a) -> double;
        static auto asin(double a) -> double;
        static auto atan(double a) -> double;
        static auto atan2(double y, double x) -> double;
        static auto cbrt(double a) -> double;
        static auto sqrt(double a) -> double;
        static auto ceil(double a) -> double;
        static auto floor(double a) -> double;
        static auto rint(double a) -> double;
        static auto round(double a) -> int64_t;
        static auto round(float a) -> int32_t;
        static auto exp(double a) -> double;
        static auto log(double a) -> double;
        static auto log10(double a) -> double;
        static auto pow(double a, double b) -> double;
        static auto random() -> double;
        static auto sin(double a) -> double;
        static auto cos(double a) -> double;
        static auto tan(double a) -> double;
        static auto sinh(double x) -> double;
        static auto cosh(double x) -> double;
        static auto tanh(double x) -> double;
        static auto toDegrees(double radians) -> double;
        static auto toRadians(double degrees) -> double;
        static auto ulp(double d) -> double;
        static auto ulp(float f) -> float;
        static auto signum(double d) -> double;
        static auto signum(float f) -> float;
        static auto hypot(double x, double y) -> double;
        static auto copySign(double magnitude, double sign) -> double;
        template <typename T> static auto max(T a, T b) -> T;
        template <typename T> static auto min(T a, T b) -> T;
    };

    inline auto MathUtil::abs(const double a) -> double
    {
        return std::fabs(a);
    }

    inline auto MathUtil::abs(const float a) -> float
    {
        return std::fabs(a);
    }

    inline auto MathUtil::abs(const int32_t a) -> int32_t
    {
        return std::abs(a);
    }

    inline auto MathUtil::abs(const int64_t a) -> int64_t
    {
        return std::labs(a);
    }

    inline auto MathUtil::acos(const double a) -> double
    {
        return std::acos(a);
    }

    inline auto MathUtil::asin(const double a) -> double
    {
        return std::asin(a);
    }

    inline auto MathUtil::atan(const double a) -> double
    {
        return std::atan(a);
    }

    inline auto MathUtil::atan2(const double y, const double x) -> double
    {
        return std::atan2(y, x);
    }

    inline auto MathUtil::cbrt(const double a) -> double
    {
        return std::cbrt(a);
    }

    inline auto MathUtil::sqrt(const double a) -> double
    {
        return std::sqrt(a);
    }

    inline auto MathUtil::ceil(const double a) -> double
    {
        return std::ceil(a);
    }

    inline auto MathUtil::floor(const double a) -> double
    {
        return std::floor(a);
    }

    inline auto MathUtil::rint(const double a) -> double
    {
        return std::nearbyint(a);
    }

    inline auto MathUtil::round(const double a) -> int64_t
    {
        return static_cast<int64_t>(std::round(a));
    }

    inline auto MathUtil::round(const float a) -> int32_t
    {
        return static_cast<int32_t>(std::round(a));
    }

    inline auto MathUtil::exp(const double a) -> double
    {
        return std::exp(a);
    }

    inline auto MathUtil::log(const double a) -> double
    {
        return std::log(a);
    }

    inline auto MathUtil::log10(const double a) -> double
    {
        return std::log10(a);
    }

    inline auto MathUtil::pow(const double a, const double b) -> double
    {
        return std::pow(a, b);
    }

    inline auto MathUtil::random() -> double
    {
        std::random_device rd{};
        std::mt19937 gen{rd()};
        std::uniform_real_distribution dis{0.0, 1.0};
        return dis(gen);
    }

    inline auto MathUtil::sin(const double a) -> double
    {
        return std::sin(a);
    }

    inline auto MathUtil::cos(const double a) -> double
    {
        return std::cos(a);
    }

    inline auto MathUtil::tan(const double a) -> double
    {
        return std::tan(a);
    }

    inline auto MathUtil::sinh(const double x) -> double
    {
        return std::sinh(x);
    }

    inline auto MathUtil::cosh(const double x) -> double
    {
        return std::cosh(x);
    }

    inline auto MathUtil::tanh(const double x) -> double
    {
        return std::tanh(x);
    }

    inline auto MathUtil::toDegrees(const double radians) -> double
    {
        return radians * 180.0 / std::numbers::pi;
    }

    inline auto MathUtil::toRadians(const double degrees) -> double
    {
        return degrees * std::numbers::pi / 180.0;
    }

    inline auto MathUtil::ulp(const double d) -> double
    {
        return std::nextafter(d, std::numeric_limits<double>::infinity()) - d;
    }

    inline auto MathUtil::ulp(const float f) -> float
    {
        return std::nextafterf(f, std::numeric_limits<float>::infinity()) - f;
    }

    inline auto MathUtil::signum(const double d) -> double
    {
        return (d > 0) - (d < 0);
    }

    inline auto MathUtil::signum(const float f) -> float
    {
        return static_cast<float>((f > 0) - (f < 0));
    }

    inline auto MathUtil::hypot(const double x, const double y) -> double
    {
        return std::hypot(x, y);
    }

    inline auto MathUtil::copySign(const double magnitude, const double sign) -> double
    {
        return std::copysign(magnitude, sign);
    }

    template <typename T> auto MathUtil::max(T a, T b) -> T
    {
        return a > b ? a : b;
    }

    template <typename T> auto MathUtil::min(T a, T b) -> T
    {
        return a < b ? a : b;
    }
}
