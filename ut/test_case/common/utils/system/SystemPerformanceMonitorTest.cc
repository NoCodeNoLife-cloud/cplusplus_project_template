#include <gtest/gtest.h>

#include "utils/system/SystemPerformanceMonitor.hpp"

namespace gtest_case
{
TEST(SystemPerformanceMonitorTest, GetMemoryUsage_ValuesAreValid)
{
    const auto [total_memory, available_memory, used_memory, memory_usage_percent] =
        fox::SystemPerformanceMonitor::GetMemoryUsage();

    EXPECT_GE(total_memory, available_memory);
    EXPECT_EQ(used_memory, total_memory - available_memory);

    EXPECT_GE(memory_usage_percent, 0.0);
    EXPECT_LE(memory_usage_percent, 100.0);
}

TEST(SystemPerformanceMonitorTest, GetCpuUsage_NormalInterval)
{
    constexpr int32_t interval = 1;

    const auto [cpu_usage_percent] = fox::SystemPerformanceMonitor::GetCpuUsage(interval);

    EXPECT_GE(cpu_usage_percent, 0.0);
    EXPECT_LE(cpu_usage_percent, 100.0);
}

TEST(SystemPerformanceMonitorTest, GetCpuUsage_ZeroInterval)
{
    constexpr int32_t interval = 0;

    const auto [cpu_usage_percent] = fox::SystemPerformanceMonitor::GetCpuUsage(interval);

    EXPECT_DOUBLE_EQ(cpu_usage_percent, 0.0);
}

TEST(SystemPerformanceMonitorTest, GetCpuUsage_NegativeInterval)
{
    constexpr int32_t interval = -1;

    const auto [cpu_usage_percent] = fox::SystemPerformanceMonitor::GetCpuUsage(interval);
    EXPECT_DOUBLE_EQ(cpu_usage_percent, 0.0);
}
} // namespace gtest_case
