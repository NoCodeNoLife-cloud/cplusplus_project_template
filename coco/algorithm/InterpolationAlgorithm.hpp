#pragma once
#include <vector>

namespace coco
{
    class InterpolationAlgorithm
    {
        static auto linearInterpolation(const std::vector<std::pair<double, double>>& dataPoints, double x) -> double;
    };
}
