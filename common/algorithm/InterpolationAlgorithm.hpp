#pragma once
#include <vector>

namespace common
{
    class InterpolationAlgorithm
    {
        static auto linearInterpolation(const std::vector<std::pair<double, double>>& dataPoints, double x) -> double;
    };
}
