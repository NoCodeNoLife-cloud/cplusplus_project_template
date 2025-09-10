#pragma once
#include <vector>

namespace fox {
/// @brief A class that provides interpolation methods.
/// This class contains static methods for performing various types of interpolation
/// on a set of data points. Currently, it supports linear interpolation.
class Interpolation {
 public:
  /// @brief Linear interpolation
  /// @param dataPoints Data points
  /// @param x X value
  /// @return Interpolated value
  static auto linearInterpolation(const std::vector<std::pair<double, double>>& dataPoints, const double x) -> double {
    if (dataPoints.size() < 2) {
      throw std::invalid_argument("At least two data points are required for linear interpolation.");
    }

    for (size_t i = 0; i < dataPoints.size() - 1; ++i) {
      if (x >= dataPoints[i].first && x <= dataPoints[i + 1].first) {
        const double x0 = dataPoints[i].first;
        const double y0 = dataPoints[i].second;
        const double x1 = dataPoints[i + 1].first;
        const double y1 = dataPoints[i + 1].second;

        return y0 + (x - x0) * (y1 - y0) / (x1 - x0);
      }
    }

    throw std::out_of_range("The x-value exceeds the range of the data points.");
  }
};
}  // namespace fox
