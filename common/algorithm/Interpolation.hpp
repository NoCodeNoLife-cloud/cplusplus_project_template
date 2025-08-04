#pragma once
#include <vector>

namespace common {
/// @brief A class that provides interpolation methods.
/// This class contains static methods for performing various types of interpolation
/// on a set of data points. Currently, it supports linear interpolation.
class Interpolation {
 public:
  /// @brief Linear interpolation
  /// @param dataPoints Data points
  /// @param x X value
  /// @return Interpolated value
  static auto linearInterpolation(const std::vector<std::pair<double, double>>& dataPoints, double x) -> double;
};
}  // namespace common
