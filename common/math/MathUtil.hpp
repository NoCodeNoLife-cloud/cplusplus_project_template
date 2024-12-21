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
        static auto abs(const double a) -> double
        {
            return std::fabs(a);
        }

        static auto abs(const float a) -> float
        {
            return std::fabs(a);
        }

        static auto abs(const int a) -> int
        {
            return std::abs(a);
        }

        static auto abs(const long a) -> long
        {
            return std::labs(a);
        }

        static auto acos(const double a) -> double
        {
            return std::acos(a);
        }

        static auto asin(const double a) -> double
        {
            return std::asin(a);
        }

        static auto atan(const double a) -> double
        {
            return std::atan(a);
        }

        static auto atan2(const double y, const double x) -> double
        {
            return std::atan2(y, x);
        }

        static auto cbrt(const double a) -> double
        {
            return std::cbrt(a);
        }

        static auto sqrt(const double a) -> double
        {
            return std::sqrt(a);
        }

        static auto ceil(const double a) -> double
        {
            return std::ceil(a);
        }

        static auto floor(const double a) -> double
        {
            return std::floor(a);
        }

        static auto rint(const double a) -> double
        {
            return std::nearbyint(a);
        }

        static auto round(const double a) -> long
        {
            return static_cast<long>(std::round(a));
        }

        static auto round(const float a) -> int
        {
            return static_cast<int>(std::round(a));
        }

        static auto exp(const double a) -> double
        {
            return std::exp(a);
        }

        static auto log(const double a) -> double
        {
            return std::log(a);
        }

        static auto log10(const double a) -> double
        {
            return std::log10(a);
        }

        static auto pow(const double a, const double b) -> double
        {
            return std::pow(a, b);
        }

        static auto random() -> double
        {
            std::random_device rd{};
            std::mt19937 gen{rd()};
            std::uniform_real_distribution dis{0.0, 1.0};
            return dis(gen);
        }

        static auto sin(const double a) -> double
        {
            return std::sin(a);
        }

        static auto cos(const double a) -> double
        {
            return std::cos(a);
        }

        static auto tan(const double a) -> double
        {
            return std::tan(a);
        }

        static auto sinh(const double x) -> double
        {
            return std::sinh(x);
        }

        static auto cosh(const double x) -> double
        {
            return std::cosh(x);
        }

        static auto tanh(const double x) -> double
        {
            return std::tanh(x);
        }

        static auto toDegrees(const double radians) -> double
        {
            return radians * 180.0 / std::numbers::pi;
        }

        static auto toRadians(const double degrees) -> double
        {
            return degrees * std::numbers::pi / 180.0;
        }

        static auto ulp(const double d) -> double
        {
            return std::nextafter(d, std::numeric_limits<double>::infinity()) - d;
        }

        static auto ulp(const float f) -> float
        {
            return std::nextafterf(f, std::numeric_limits<float>::infinity()) - f;
        }

        static auto signum(const double d) -> double
        {
            return (d > 0) - (d < 0);
        }

        static auto signum(const float f) -> float
        {
            return static_cast<float>((f > 0) - (f < 0));
        }

        static auto hypot(const double x, const double y) -> double
        {
            return std::hypot(x, y);
        }

        static auto copySign(const double magnitude, const double sign) -> double
        {
            return std::copysign(magnitude, sign);
        }

        template <typename T>
        static auto max(T a, T b) -> T
        {
            return a > b ? a : b;
        }

        template <typename T>
        static auto min(T a, T b) -> T
        {
            return a < b ? a : b;
        }
    };
}
