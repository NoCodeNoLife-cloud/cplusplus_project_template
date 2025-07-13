#pragma once
#include <vector>

namespace coco
{
    class InterpolationAlgorithm
    {
    public:
        static auto linearInterpolation(const std::vector<std::pair<double, double>>& dataPoints, double x) -> double;
    };
}
