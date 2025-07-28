#pragma once
#include <vector>

namespace common {
class Interpolation {
 public:
  static auto linearInterpolation(
      const std::vector<std::pair<double, double>>& dataPoints, double x)
      -> double;
};
}  // namespace common
