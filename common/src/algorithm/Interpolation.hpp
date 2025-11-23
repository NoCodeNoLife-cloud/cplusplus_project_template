#pragma once
#include <algorithm>
#include <vector>

namespace common
{
    /// @brief A class that provides interpolation methods.
    /// This class contains static methods for performing various types of interpolation
    /// on a set of data points.
    class Interpolation
    {
    public:
        /// @brief Linear interpolation
        /// @param dataPoints Data points, must be sorted by x value
        /// @param x X value
        /// @return Interpolated value
        /// @throws std::invalid_argument if dataPoints has less than 2 points
        /// @throws std::out_of_range if x is outside the range of data points
        static auto linear(const std::vector<std::pair<double, double>>& dataPoints,
                           double x)
            -> double;

        /// @brief Nearest neighbor interpolation
        /// @param dataPoints Data points, must be sorted by x value
        /// @param x X value
        /// @return Interpolated value (nearest y value)
        /// @throws std::invalid_argument if dataPoints is empty
        /// @throws std::out_of_range if x is outside the range of data points
        static auto nearest(const std::vector<std::pair<double, double>>& dataPoints,
                            double x)
            -> double;

        /// @brief Cubic interpolation using four points
        /// @param dataPoints Data points, must be sorted by x value and have at least 4 points
        /// @param x X value
        /// @return Interpolated value
        /// @throws std::invalid_argument if dataPoints has less than 4 points
        /// @throws std::out_of_range if x is outside the valid range for cubic interpolation
        static auto cubic(const std::vector<std::pair<double, double>>& dataPoints,
                          double x)
            -> double;

    private:
        /// @brief Validate data points
        /// @param dataPoints Data points to validate
        /// @param minSize Minimum required size
        static void validateDataPoints(const std::vector<std::pair<double, double>>& dataPoints,
                                       size_t minSize);

        /// @brief Find the lower bound index for x value
        /// @param dataPoints Data points (sorted)
        /// @param x X value
        /// @return Index of the lower bound segment
        static size_t findLowerBound(const std::vector<std::pair<double, double>>& dataPoints,
                                     double x);

        /// @brief Find the index of the closest data point to x
        /// @param dataPoints Data points (sorted)
        /// @param x X value
        /// @return Index of the closest point
        static size_t findClosestPoint(const std::vector<std::pair<double, double>>& dataPoints,
                                       double x);
    };
}
