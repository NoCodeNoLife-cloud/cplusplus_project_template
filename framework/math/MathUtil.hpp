#pragma once
#include <format>

namespace framework::math {
  class MathUtil abstract {
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
    template <typename T>
    static auto max(T a, T b) -> T;
    template <typename T>
    static auto min(T a, T b) -> T;
  };

  template <typename T>
  auto MathUtil::max(T a, T b) -> T {
    return a > b ? a : b;
  }

  template <typename T>
  auto MathUtil::min(T a, T b) -> T {
    return a < b ? a : b;
  }
} // namespace framework::math
