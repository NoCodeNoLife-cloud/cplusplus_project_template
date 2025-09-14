#include <gtest/gtest.h>

#include "algorithm/Interpolation.hpp"

namespace gtest_ut
{
TEST(InterpolationAlgorithmTest, LinearBasic)
{
    const std::vector<std::pair<double, double>> dataPoints = {{0.0, 0.0}, {1.0, 1.0}, {2.0, 4.0}};
    EXPECT_DOUBLE_EQ(fox::Interpolation::linear(dataPoints, 0.5), 0.5);
    EXPECT_DOUBLE_EQ(fox::Interpolation::linear(dataPoints, 1.5), 2.5);
}

TEST(InterpolationAlgorithmTest, LinearEdgeCases)
{
    const std::vector<std::pair<double, double>> dataPoints = {{0.0, 0.0}, {1.0, 1.0}};
    EXPECT_DOUBLE_EQ(fox::Interpolation::linear(dataPoints, 0.0), 0.0);
    EXPECT_DOUBLE_EQ(fox::Interpolation::linear(dataPoints, 1.0), 1.0);
}

TEST(InterpolationAlgorithmTest, LinearOutOfRange)
{
    std::vector<std::pair<double, double>> dataPoints = {{0.0, 0.0}, {1.0, 1.0}};
    EXPECT_THROW(fox::Interpolation::linear(dataPoints, -0.1), std::out_of_range);
    EXPECT_THROW(fox::Interpolation::linear(dataPoints, 1.1), std::out_of_range);
}

TEST(InterpolationAlgorithmTest, LinearNotEnoughDataPoints)
{
    const std::vector<std::pair<double, double>> dataPoints = {{0.0, 0.0}};
    EXPECT_THROW(fox::Interpolation::linear(dataPoints, 0.0), std::invalid_argument);
}

TEST(InterpolationAlgorithmTest, NearestBasic)
{
    const std::vector<std::pair<double, double>> dataPoints = {{0.0, 0.0}, {1.0, 1.0}, {2.0, 4.0}};
    EXPECT_DOUBLE_EQ(fox::Interpolation::nearest(dataPoints, 0.4), 0.0); // Closer to point (0.0, 0.0)
    EXPECT_DOUBLE_EQ(fox::Interpolation::nearest(dataPoints, 0.6), 1.0); // Closer to point (1.0, 1.0)
    EXPECT_DOUBLE_EQ(fox::Interpolation::nearest(dataPoints, 1.6), 4.0); // Closer to point (2.0, 4.0)
}

TEST(InterpolationAlgorithmTest, NearestEdgeCases)
{
    const std::vector<std::pair<double, double>> dataPoints = {{0.0, 0.0}, {1.0, 1.0}};
    EXPECT_DOUBLE_EQ(fox::Interpolation::nearest(dataPoints, 0.0), 0.0);
    EXPECT_DOUBLE_EQ(fox::Interpolation::nearest(dataPoints, 1.0), 1.0);
    EXPECT_DOUBLE_EQ(fox::Interpolation::nearest(dataPoints, 0.4), 0.0);
    EXPECT_DOUBLE_EQ(fox::Interpolation::nearest(dataPoints, 0.6), 1.0);
}

TEST(InterpolationAlgorithmTest, NearestSinglePoint)
{
    const std::vector<std::pair<double, double>> dataPoints = {{1.0, 5.0}};
    EXPECT_DOUBLE_EQ(fox::Interpolation::nearest(dataPoints, 0.0), 5.0);
    EXPECT_DOUBLE_EQ(fox::Interpolation::nearest(dataPoints, 1.0), 5.0);
    EXPECT_DOUBLE_EQ(fox::Interpolation::nearest(dataPoints, 2.0), 5.0);
}

TEST(InterpolationAlgorithmTest, NearestNotEnoughDataPoints)
{
    const std::vector<std::pair<double, double>> dataPoints = {};
    EXPECT_THROW(fox::Interpolation::nearest(dataPoints, 0.0), std::invalid_argument);
}

TEST(InterpolationAlgorithmTest, CubicBasic)
{
    const std::vector<std::pair<double, double>> dataPoints = {
        {0.0, 0.0}, {1.0, 1.0}, {2.0, 8.0}, {3.0, 27.0}, {4.0, 64.0}};
    // For cubic interpolation, we can only interpolate between points at indices 1 and 2 (values 1.0 and 2.0)
    // because we need one point before and one point after the segment
    EXPECT_DOUBLE_EQ(fox::Interpolation::cubic(dataPoints, 1.5), 3.375); // Should be 1.5^3 = 3.375
}

TEST(InterpolationAlgorithmTest, CubicNotEnoughDataPoints)
{
    const std::vector<std::pair<double, double>> dataPoints = {{0.0, 0.0}, {1.0, 1.0}, {2.0, 4.0}};
    EXPECT_THROW(fox::Interpolation::cubic(dataPoints, 1.0), std::invalid_argument);
}

TEST(InterpolationAlgorithmTest, CubicInsufficientPointsForInterpolation)
{
    const std::vector<std::pair<double, double>> dataPoints = {{0.0, 0.0}, {1.0, 1.0}, {2.0, 4.0}, {3.0, 9.0}};
    EXPECT_THROW(fox::Interpolation::cubic(dataPoints, 0.0), std::out_of_range);
    EXPECT_THROW(fox::Interpolation::cubic(dataPoints, 3.0), std::out_of_range);
}

TEST(InterpolationAlgorithmTest, UnsortedDataPoints)
{
    const std::vector<std::pair<double, double>> dataPoints = {{1.0, 1.0}, {0.0, 0.0}, {2.0, 4.0}}; // Not sorted
    EXPECT_THROW(fox::Interpolation::linear(dataPoints, 0.5), std::invalid_argument);
    EXPECT_THROW(fox::Interpolation::nearest(dataPoints, 0.5), std::invalid_argument);
    EXPECT_THROW(fox::Interpolation::cubic(dataPoints, 0.5), std::invalid_argument);
}
} // namespace gtest_ut
