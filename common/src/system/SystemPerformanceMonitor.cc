#include "src/system/SystemPerformanceMonitor.hpp"

#include <windows.h>

#include <chrono>
#include <cstdint>
#include <thread>

namespace common
{
    auto SystemPerformanceMonitor::GetMemoryUsage() noexcept -> MemoryUsage
    {
        MemoryUsage memUsage{};
        MEMORYSTATUSEX memInfo;
        memInfo.dwLength = sizeof(MEMORYSTATUSEX);
        GlobalMemoryStatusEx(&memInfo);
        memUsage.total_memory = memInfo.ullTotalPhys;
        memUsage.available_memory = memInfo.ullAvailPhys;
        memUsage.used_memory = memUsage.total_memory - memUsage.available_memory;
        memUsage.memory_usage_percent = static_cast<double>(memUsage.used_memory) / static_cast<double>(memUsage.
            total_memory) * 100.0;
        return memUsage;
    }

    auto SystemPerformanceMonitor::GetCpuUsage(const int32_t interval) noexcept -> CpuUsage
    {
        CpuUsage cpuUsage{};
        FILETIME idleTime1, kernelTime1, userTime1;
        FILETIME idleTime2, kernelTime2, userTime2;
        ULARGE_INTEGER idle1, kernel1, user1;
        ULARGE_INTEGER idle2, kernel2, user2;

        GetSystemTimes(&idleTime1, &kernelTime1, &userTime1);
        idle1.LowPart = idleTime1.dwLowDateTime;
        idle1.HighPart = idleTime1.dwHighDateTime;
        kernel1.LowPart = kernelTime1.dwLowDateTime;
        kernel1.HighPart = kernelTime1.dwHighDateTime;
        user1.LowPart = userTime1.dwLowDateTime;
        user1.HighPart = userTime1.dwHighDateTime;

        std::this_thread::sleep_for(std::chrono::seconds(interval));

        GetSystemTimes(&idleTime2, &kernelTime2, &userTime2);
        idle2.LowPart = idleTime2.dwLowDateTime;
        idle2.HighPart = idleTime2.dwHighDateTime;
        kernel2.LowPart = kernelTime2.dwLowDateTime;
        kernel2.HighPart = kernelTime2.dwHighDateTime;
        user2.LowPart = userTime2.dwLowDateTime;
        user2.HighPart = userTime2.dwHighDateTime;

        const ULONGLONG idleDiff = idle2.QuadPart - idle1.QuadPart;
        const ULONGLONG kernelDiff = kernel2.QuadPart - kernel1.QuadPart;
        const ULONGLONG userDiff = user2.QuadPart - user1.QuadPart;

        if (const ULONGLONG totalDiff = kernelDiff + userDiff; totalDiff != 0)
        {
            cpuUsage.cpu_usage_percent = (static_cast<double>(totalDiff) - static_cast<double>(idleDiff)) * 100.0 /
                static_cast<double>(totalDiff);
        }
        else
        {
            cpuUsage.cpu_usage_percent = 0.0;
        }

        return cpuUsage;
    }
}
