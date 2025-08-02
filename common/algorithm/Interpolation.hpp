#pragma once
#include <vector>

namespace common {
class Interpolation {
 public:
  /// @brief Linear interpolation
  /// @param dataPoints Data points
  /// @param x X value
  /// @return Interpolated value
  static auto linearInterpolation(const std::vector<std::pair<double, double>>& dataPoints, double x) -> double;
};
}  // namespace common
