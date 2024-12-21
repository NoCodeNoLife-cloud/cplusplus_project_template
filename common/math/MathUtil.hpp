#pragma once
#include <cmath>
#include <format>
#include <limits>
#include <numbers>
#include <random>

namespace common::math {
/// \class MathUtil
/// \brief Provides a collection of mathematical functions and constants.
/// \details This abstract class offers a variety of static methods for performing mathematical operations such as
/// trigonometric, logarithmic, and exponential calculations. It also includes utility functions for rounding, finding
/// absolute values, and generating random numbers. The Math class is designed to be a comprehensive library for
/// mathematical computations.
class MathUtil abstract {
public:
  /// \brief Returns the absolute value of a double value.
  /// \details If the argument is not negative, the result is the same as the argument. If the argument is negative, the
  /// result is the negation of the argument.
  /// \param[in] a The double value whose absolute value is to be determined.
  /// \return The absolute value of the argument.
  static auto abs(const double a) -> double {
    return std::fabs(a);
  }

  /// \brief Returns the absolute value of a float value.
  /// \details If the argument is not negative, the result is the same as the argument. If the argument is negative, the
  /// result is the negation of the argument.
  /// \param[in] a The float value whose absolute value is to be determined.
  /// \return The absolute value of the argument.
  static auto abs(const float a) -> float {
    return std::fabs(a);
  }

  /// \brief Returns the absolute value of an int value.
  /// \details If the argument is not negative, the result is the same as the argument. If the argument is negative, the
  /// result is the negation of the argument.
  /// \param[in] a The int value whose absolute value is to be determined.
  /// \return The absolute value of the argument.
  static auto abs(const int a) -> int {
    return std::abs(a);
  }

  /// \brief Returns the absolute value of a long value.
  /// \details If the argument is not negative, the result is the same as the argument. If the argument is negative, the
  /// result is the negation of the argument.
  /// \param[in] a The long value whose absolute value is to be determined.
  /// \return The absolute value of the argument.
  static auto abs(const long a) -> long {
    return std::labs(a);
  }

  /// \brief Returns the arc cosine of a double value.
  /// \details The arc cosine is the angle whose cosine is the specified number.
  /// The returned angle is in the range [0.0, pi] radians.
  /// \param[in] a The double value whose arc cosine is to be determined.
  /// \return The arc cosine of the argument.
  /// \throws std::domain_error If the argument is outside the range [-1.0, 1.0].
  static auto acos(const double a) -> double {
    return std::acos(a);
  }

  /// \brief Returns the arc sine of a double value.
  /// \details The arc sine is the angle whose sine is the specified number.
  /// The returned angle is in the range [-pi/2, pi/2] radians.
  /// \param[in] a The double value whose arc sine is to be determined.
  /// \return The arc sine of the argument.
  /// \throws std::domain_error If the argument is outside the range [-1.0, 1.0].
  static auto asin(const double a) -> double {
    return std::asin(a);
  }

  /// \brief Returns the arc tangent of a double value.
  /// \details The arc tangent is the angle whose tangent is the specified number.
  /// The returned angle is in the range [-pi/2, pi/2] radians.
  /// \param[in] a The double value whose arc tangent is to be determined.
  /// \return The arc tangent of the argument.
  static auto atan(const double a) -> double {
    return std::atan(a);
  }

  /// \brief Returns the angle in radians from the x-axis to the point (y, x).
  /// \details The angle is in the range [-pi, pi] radians.
  /// \param[in] y The y-coordinate of the point.
  /// \param[in] x The x-coordinate of the point.
  /// \return The angle in radians from the x-axis to the point (y, x).
  static auto atan2(const double y, const double x) -> double {
    return std::atan2(y, x);
  }

  /// \brief Returns the cube root of a double value.
  /// \details The cube root is the value which, when multiplied by itself three times, produces the argument.
  /// \param[in] a The double value whose cube root is to be determined.
  /// \return The cube root of the argument.
  static auto cbrt(const double a) -> double {
    return std::cbrt(a);
  }

  /// \brief Returns the square root of a double value.
  /// \details The square root is the value which, when multiplied by itself, produces the argument.
  /// \param[in] a The double value whose square root is to be determined.
  /// \return The square root of the argument.
  static auto sqrt(const double a) -> double {
    return std::sqrt(a);
  }

  /// \brief Returns the smallest integer that is greater than or equal to the argument.
  /// \details The ceiling of a double value is the smallest integer that is greater than or equal to the argument.
  /// \param[in] a The double value whose ceiling is to be determined.
  /// \return The smallest integer that is greater than or equal to the argument.
  static auto ceil(const double a) -> double {
    return std::ceil(a);
  }

  /// \brief Returns the largest integer that is less than or equal to the argument.
  /// \details The floor of a double value is the largest integer that is less than or equal to the argument.
  /// \param[in] a The double value whose floor is to be determined.
  /// \return The largest integer that is less than or equal to the argument.
  static auto floor(const double a) -> double {
    return std::floor(a);
  }

  /// \brief Returns the double value that is closest in value to the argument and is equal to a mathematical integer.
  /// \details If two double values that are mathematical integers are equally close to the value of the argument, the
  /// result is the integer value that is even.
  /// \param[in] a The double value whose integer value closest to the argument is to be determined.
  /// \return The double value that is closest in value to the argument and is equal to a mathematical integer.
  static auto rint(const double a) -> double {
    return std::nearbyint(a);
  }

  /// \brief Returns the closest long to the argument, with ties rounding to positive infinity.
  /// \details The value of the argument is rounded to the nearest long value.
  /// If the argument is halfway between two long values, the result is the long value that is closer to positive
  /// infinity.
  /// \param[in] a The double value whose rounded value is to be determined.
  /// \return The closest long to the argument, with ties rounding to positive infinity.
  static auto round(const double a) -> long {
    return static_cast<long>(std::round(a));
  }

  /// \brief Returns the closest int to the argument, with ties rounding to positive infinity.
  /// \details The value of the argument is rounded to the nearest int value.
  /// If the argument is halfway between two int values, the result is the int value that is closer to positive infinity.
  /// \param[in] a The float value whose rounded value is to be determined.
  /// \return The closest int to the argument, with ties rounding to positive infinity.
  static auto round(const float a) -> int {
    return static_cast<int>(std::round(a));
  }

  /// \brief Returns Euler's number e raised to the power of a double value.
  /// \details This function returns Euler's number e raised to the power of the argument.
  /// \param[in] a The double value whose exponential value is to be determined.
  /// \return Euler's number e raised to the power of the argument.
  static auto exp(const double a) -> double {
    return std::exp(a);
  }

  /// \brief Returns the natural logarithm of a double value.
  /// \details This function returns the natural logarithm of the argument.
  /// \param[in] a The double value whose natural logarithm is to be determined.
  /// \return The natural logarithm of the argument.
  static auto log(const double a) -> double {
    return std::log(a);
  }

  /// \brief Returns the base 10 logarithm of a double value.
  /// \details This function returns the base 10 logarithm of the argument.
  /// \param[in] a The double value whose base 10 logarithm is to be determined.
  /// \return The base 10 logarithm of the argument.
  static auto log10(const double a) -> double {
    return std::log10(a);
  }

  /// \brief Raises a double value to the power of another double value.
  /// \details This function computes the value of the first argument raised to the power of the second argument.
  /// \param[in] a The base value to be raised to the power.
  /// \param[in] b The exponent value.
  /// \return The result of raising the base to the power of the exponent.
  /// \throws std::domain_error If the base is zero and the exponent is less than or equal to zero.
  static auto pow(const double a, const double b) -> double {
    return std::pow(a, b);
  }

  /// \brief Returns a random double value between 0.0 and 1.0.
  /// \details This function uses the Mersenne Twister engine to generate a random double value.
  /// \return A random double value between 0.0 and 1.0.
  static auto random() -> double {
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::uniform_real_distribution dis{0.0, 1.0};
    return dis(gen);
  }

  /// \brief Returns the sine of a double value.
  /// \details This function returns the sine of the argument.
  /// \param[in] a The double value whose sine is to be determined.
  /// \return The sine of the argument.
  static auto sin(const double a) -> double {
    return std::sin(a);
  }

  /// \brief Returns the cosine of a double value.
  /// \details This function returns the cosine of the argument.
  /// \param[in] a The double value whose cosine is to be determined.
  /// \return The cosine of the argument.
  static auto cos(const double a) -> double {
    return std::cos(a);
  }

  /// \brief Returns the tangent of a double value.
  /// \details This function returns the tangent of the argument.
  /// \param[in] a The double value whose tangent is to be determined.
  /// \return The tangent of the argument.
  static auto tan(const double a) -> double {
    return std::tan(a);
  }

  /// \brief Returns the hyperbolic sine of a double value.
  /// \details This function returns the hyperbolic sine of the argument.
  /// \param[in] x The double value whose hyperbolic sine is to be determined.
  /// \return The hyperbolic sine of the argument.
  static auto sinh(const double x) -> double {
    return std::sinh(x);
  }

  /// \brief Returns the hyperbolic cosine of a double value.
  /// \details This function returns the hyperbolic cosine of the argument.
  /// \param[in] x The double value whose hyperbolic cosine is to be determined.
  /// \return The hyperbolic cosine of the argument.
  static auto cosh(const double x) -> double {
    return std::cosh(x);
  }

  /// \brief Returns the hyperbolic tangent of a double value.
  /// \details This function returns the hyperbolic tangent of the argument.
  /// \param[in] x The double value whose hyperbolic tangent is to be determined.
  /// \return The hyperbolic tangent of the argument.
  static auto tanh(const double x) -> double {
    return std::tanh(x);
  }

  /// \brief Converts radians to degrees.
  /// \details This function converts a double value in radians to an equivalent double value in degrees.
  /// \param[in] radians The double value in radians to be converted.
  /// \return The equivalent double value in degrees.
  static auto toDegrees(const double radians) -> double {
    return radians * 180.0 / std::numbers::pi;
  }

  /// \brief Converts degrees to radians.
  /// \details This function converts a double value in degrees to an equivalent double value in radians.
  /// \param[in] degrees The double value in degrees to be converted.
  /// \return The equivalent double value in radians.
  static auto toRadians(const double degrees) -> double {
    return degrees * std::numbers::pi / 180.0;
  }

  /// \brief Returns the unit in the last place (ULP) of a double value.
  /// \details The ULP is the positive distance between the given double value and the next larger representable double
  /// value.
  /// \param[in] d The double value whose ULP is to be determined.
  /// \return The ULP of the argument.
  static auto ulp(const double d) -> double {
    return std::nextafter(d, std::numeric_limits<double>::infinity()) - d;
  }

  /// \brief Returns the unit in the last place (ULP) of a float value.
  /// \details The ULP is the positive distance between the given float value and the next larger representable float
  /// value.
  /// \param[in] f The float value whose ULP is to be determined.
  /// \return The ULP of the argument.
  static auto ulp(const float f) -> float {
    return std::nextafterf(f, std::numeric_limits<float>::infinity()) - f;
  }

  /// \brief Returns the signum function of a double value.
  /// \details The signum function returns -1 if the argument is less than zero, 0 if the argument is zero, and 1 if the
  /// argument is greater than zero.
  /// \param[in] d The double value whose signum is to be determined.
  /// \return The signum of the argument.
  static auto signum(const double d) -> double {
    return (d > 0) - (d < 0);
  }

  /// \brief Returns the signum function of a float value.
  /// \details The signum function returns -1.0f if the argument is less than zero, 0.0f if the argument is zero, and 1.0f
  /// if the argument is greater than zero.
  /// \param[in] f The float value whose signum is to be determined.
  /// \return The signum of the argument.
  static auto signum(const float f) -> float {
    return static_cast<float>((f > 0) - (f < 0));
  }

  /// \brief Returns the square root of the sum of the squares of two double values.
  /// \details This function returns the square root of the sum of the squares of the two arguments.
  /// \param[in] x The first double value.
  /// \param[in] y The second double value.
  /// \return The square root of the sum of the squares of the two arguments.
  static auto hypot(const double x, const double y) -> double {
    return std::hypot(x, y);
  }

  /// \brief Returns the first floating-point argument with the sign of the second floating-point argument.
  /// \details This function returns the value of the first argument with the sign of the second argument.
  /// \param[in] magnitude The double value whose magnitude is used.
  /// \param[in] sign The double value whose sign is used.
  /// \return The first argument with the sign of the second argument.
  static auto copySign(const double magnitude, const double sign) -> double {
    return std::copysign(magnitude, sign);
  }

  /// \brief Returns the maximum value of two values.
  /// \details This function returns the maximum value of the two arguments.
  /// \param[in] a The first value to compare.
  /// \param[in] b The second value to compare.
  /// \return The maximum value of the two arguments.
  template <typename T>
  static auto max(T a, T b) -> T {
    return a > b ? a : b;
  }

  /// \brief Returns the minimum value of two values.
  /// \details This function returns the minimum value of the two arguments.
  /// \param[in] a The first value to compare.
  /// \param[in] b The second value to compare.
  /// \return The minimum value of the two arguments.
  template <typename T>
  static auto min(T a, T b) -> T {
    return a < b ? a : b;
  }
};
}
