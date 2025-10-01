#pragma once
#include <algorithm>
#include <stdexcept>
#include <vector>

namespace fox
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
        static auto linear(const std::vector<std::pair<double, double>>& dataPoints, double x) -> double;

        /// @brief Nearest neighbor interpolation
        /// @param dataPoints Data points, must be sorted by x value
        /// @param x X value
        /// @return Interpolated value (nearest y value)
        /// @throws std::invalid_argument if dataPoints is empty
        /// @throws std::out_of_range if x is outside the range of data points
        static auto nearest(const std::vector<std::pair<double, double>>& dataPoints, double x) -> double;

        /// @brief Cubic interpolation using four points
        /// @param dataPoints Data points, must be sorted by x value and have at least 4 points
        /// @param x X value
        /// @return Interpolated value
        /// @throws std::invalid_argument if dataPoints has less than 4 points
        /// @throws std::out_of_range if x is outside the valid range for cubic interpolation
        static auto cubic(const std::vector<std::pair<double, double>>& dataPoints, double x) -> double;

    private:
        /// @brief Validate data points
        /// @param dataPoints Data points to validate
        /// @param minSize Minimum required size
        static void validateDataPoints(const std::vector<std::pair<double, double>>& dataPoints, size_t minSize);

        /// @brief Find the lower bound index for x value
        /// @param dataPoints Data points (sorted)
        /// @param x X value
        /// @return Index of the lower bound segment
        static size_t findLowerBound(const std::vector<std::pair<double, double>>& dataPoints, double x);

        /// @brief Find the index of the closest data point to x
        /// @param dataPoints Data points (sorted)
        /// @param x X value
        /// @return Index of the closest point
        static size_t findClosestPoint(const std::vector<std::pair<double, double>>& dataPoints, double x);
    };

    inline auto Interpolation::linear(const std::vector<std::pair<double, double>>& dataPoints,
                                      const double x) -> double
    {
        validateDataPoints(dataPoints, 2);

        const size_t index = findLowerBound(dataPoints, x);

        const double x0 = dataPoints[index].first;
        const double y0 = dataPoints[index].second;
        const double x1 = dataPoints[index + 1].first;
        const double y1 = dataPoints[index + 1].second;

        return y0 + (x - x0) * (y1 - y0) / (x1 - x0);
    }

    inline auto Interpolation::nearest(const std::vector<std::pair<double, double>>& dataPoints,
                                       const double x) -> double
    {
        validateDataPoints(dataPoints, 1);

        if (dataPoints.size() == 1)
        {
            return dataPoints[0].second;
        }

        const size_t index = findClosestPoint(dataPoints, x);
        return dataPoints[index].second;
    }

    inline auto Interpolation::cubic(const std::vector<std::pair<double, double>>& dataPoints, const double x) -> double
    {
        validateDataPoints(dataPoints, 4);

        // Find the segment that contains x
        const size_t index = findLowerBound(dataPoints, x);

        // In the cubic method implementation, replace this:
        if (index == 0 || index >= dataPoints.size() - 2)
        {
            throw std::out_of_range("Insufficient points for cubic interpolation at the given x value.");
        }

        // With this more accurate check:
        if (index >= dataPoints.size() - 2)
        {
            throw std::out_of_range("Insufficient points for cubic interpolation at the given x value.");
        }


        // Use four points for cubic interpolation
        const double x0 = dataPoints[index - 1].first;
        const double y0 = dataPoints[index - 1].second;
        const double x1 = dataPoints[index].first;
        const double y1 = dataPoints[index].second;
        const double x2 = dataPoints[index + 1].first;
        const double y2 = dataPoints[index + 1].second;
        const double x3 = dataPoints[index + 2].first;
        const double y3 = dataPoints[index + 2].second;

        // Calculate cubic interpolation using Lagrange polynomial
        const double l0 = ((x - x1) * (x - x2) * (x - x3)) / ((x0 - x1) * (x0 - x2) * (x0 - x3));
        const double l1 = ((x - x0) * (x - x2) * (x - x3)) / ((x1 - x0) * (x1 - x2) * (x1 - x3));
        const double l2 = ((x - x0) * (x - x1) * (x - x3)) / ((x2 - x0) * (x2 - x1) * (x2 - x3));
        const double l3 = ((x - x0) * (x - x1) * (x - x2)) / ((x3 - x0) * (x3 - x1) * (x3 - x2));

        return y0 * l0 + y1 * l1 + y2 * l2 + y3 * l3;
    }

    inline void Interpolation::validateDataPoints(const std::vector<std::pair<double, double>>& dataPoints,
                                                  const size_t minSize)
    {
        if (dataPoints.size() < minSize)
        {
            throw std::invalid_argument("At least " + std::to_string(minSize) +
                " data point(s) required for this interpolation method.");
        }

        // Check if data points are sorted
        for (size_t i = 1; i < dataPoints.size(); ++i)
        {
            if (dataPoints[i].first < dataPoints[i - 1].first)
            {
                throw std::invalid_argument("Data points must be sorted by x value.");
            }
        }
    }

    inline size_t Interpolation::findLowerBound(const std::vector<std::pair<double, double>>& dataPoints,
                                                const double x)
    {
        if (x < dataPoints.front().first || x > dataPoints.back().first)
        {
            throw std::out_of_range("The x-value exceeds the range of the data points.");
        }

        // Binary search for the segment
        auto it = std::lower_bound(dataPoints.begin(), dataPoints.end(), x,
                                   [](const std::pair<double, double>& a, const double b) { return a.first < b; });

        // Handle edge case where x exactly matches a data point
        if (it != dataPoints.end() && it->first == x)
        {
            if (it != dataPoints.end() - 1)
            {
                return std::distance(dataPoints.begin(), it);
            }
            // If it's the last point, use the previous segment
            return std::distance(dataPoints.begin(), it) - 1;
        }

        // Return the index of the lower bound
        return std::distance(dataPoints.begin(), it) - 1;
    }

    inline size_t Interpolation::findClosestPoint(const std::vector<std::pair<double, double>>& dataPoints,
                                                  const double x)
    {
        if (x <= dataPoints.front().first)
        {
            return 0;
        }

        if (x >= dataPoints.back().first)
        {
            return dataPoints.size() - 1;
        }

        const auto it = std::lower_bound(dataPoints.begin(), dataPoints.end(), x,
                                         [](const std::pair<double, double>& a, const double b)
                                         {
                                             return a.first < b;
                                         });

        const auto& nextIt = it;
        const auto prevIt = it != dataPoints.begin() ? it - 1 : it;

        const double distToNext = std::abs(nextIt->first - x);
        const double distToPrev = std::abs(prevIt->first - x);

        return distToPrev <= distToNext
                   ? std::distance(dataPoints.begin(), prevIt)
                   : std::distance(dataPoints.begin(), nextIt);
    }
}
