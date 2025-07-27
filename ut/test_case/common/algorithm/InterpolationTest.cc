#include <gtest/gtest.h>

#include "algorithm/Interpolation.hpp"

namespace gtest_ut
{
    TEST(InterpolationAlgorithmTest, LinearInterpolationBasic)
    {
        const std::vector<std::pair<double, double>> dataPoints = {{0.0, 0.0}, {1.0, 1.0}, {2.0, 4.0}};
        EXPECT_DOUBLE_EQ(common::Interpolation::linearInterpolation(dataPoints, 0.5), 0.5);
        EXPECT_DOUBLE_EQ(common::Interpolation::linearInterpolation(dataPoints, 1.5), 2.5);
    }

    TEST(InterpolationAlgorithmTest, LinearInterpolationEdgeCases)
    {
        const std::vector<std::pair<double, double>> dataPoints = {{0.0, 0.0}, {1.0, 1.0}};
        EXPECT_DOUBLE_EQ(common::Interpolation::linearInterpolation(dataPoints, 0.0), 0.0);
        EXPECT_DOUBLE_EQ(common::Interpolation::linearInterpolation(dataPoints, 1.0), 1.0);
    }

    TEST(InterpolationAlgorithmTest, LinearInterpolationOutOfRange)
    {
        std::vector<std::pair<double, double>> dataPoints = {{0.0, 0.0}, {1.0, 1.0}};
        EXPECT_THROW(common::Interpolation::linearInterpolation(dataPoints, -0.1), std::out_of_range);
        EXPECT_THROW(common::Interpolation::linearInterpolation(dataPoints, 1.1), std::out_of_range);
    }

    TEST(InterpolationAlgorithmTest, LinearInterpolationNotEnoughDataPoints)
    {
        const std::vector<std::pair<double, double>> dataPoints = {{0.0, 0.0}};
        EXPECT_THROW(common::Interpolation::linearInterpolation(dataPoints, 0.0), std::invalid_argument);
    }
}
