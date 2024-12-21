#include "MathUtil.hpp"

#include <cmath>
#include <limits>
#include <numbers>
#include <random>

namespace framework::math {

auto MathUtil::abs(const double a) -> double { return std::fabs(a); }

auto MathUtil::abs(const float a) -> float { return std::fabs(a); }

auto MathUtil::abs(const int32_t a) -> int32_t { return std::abs(a); }

auto MathUtil::abs(const int64_t a) -> int64_t { return std::labs(a); }

auto MathUtil::acos(const double a) -> double { return std::acos(a); }

auto MathUtil::asin(const double a) -> double { return std::asin(a); }

auto MathUtil::atan(const double a) -> double { return std::atan(a); }

auto MathUtil::atan2(const double y, const double x) -> double { return std::atan2(y, x); }

auto MathUtil::cbrt(const double a) -> double { return std::cbrt(a); }

auto MathUtil::sqrt(const double a) -> double { return std::sqrt(a); }

auto MathUtil::ceil(const double a) -> double { return std::ceil(a); }

auto MathUtil::floor(const double a) -> double { return std::floor(a); }

auto MathUtil::rint(const double a) -> double { return std::nearbyint(a); }

auto MathUtil::round(const double a) -> int64_t { return static_cast<int64_t>(std::round(a)); }

auto MathUtil::round(const float a) -> int32_t { return static_cast<int32_t>(std::round(a)); }

auto MathUtil::exp(const double a) -> double { return std::exp(a); }

auto MathUtil::log(const double a) -> double { return std::log(a); }

auto MathUtil::log10(const double a) -> double { return std::log10(a); }

auto MathUtil::pow(const double a, const double b) -> double { return std::pow(a, b); }

auto MathUtil::random() -> double {
  std::random_device rd{};
  std::mt19937 gen{rd()};
  std::uniform_real_distribution dis{0.0, 1.0};
  return dis(gen);
}

auto MathUtil::sin(const double a) -> double { return std::sin(a); }

auto MathUtil::cos(const double a) -> double { return std::cos(a); }

auto MathUtil::tan(const double a) -> double { return std::tan(a); }

auto MathUtil::sinh(const double x) -> double { return std::sinh(x); }

auto MathUtil::cosh(const double x) -> double { return std::cosh(x); }

auto MathUtil::tanh(const double x) -> double { return std::tanh(x); }

auto MathUtil::toDegrees(const double radians) -> double { return radians * 180.0 / std::numbers::pi; }

auto MathUtil::toRadians(const double degrees) -> double { return degrees * std::numbers::pi / 180.0; }

auto MathUtil::ulp(const double d) -> double { return std::nextafter(d, std::numeric_limits<double>::infinity()) - d; }

auto MathUtil::ulp(const float f) -> float { return std::nextafterf(f, std::numeric_limits<float>::infinity()) - f; }

auto MathUtil::signum(const double d) -> double { return (d > 0) - (d < 0); }

auto MathUtil::signum(const float f) -> float { return static_cast<float>((f > 0) - (f < 0)); }

auto MathUtil::hypot(const double x, const double y) -> double { return std::hypot(x, y); }

auto MathUtil::copySign(const double magnitude, const double sign) -> double { return std::copysign(magnitude, sign); }

}  // namespace framework::math
