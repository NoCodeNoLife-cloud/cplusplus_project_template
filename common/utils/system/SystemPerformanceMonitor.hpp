#pragma once
#include <windows.h>

namespace common
{
    struct MemoryUsage
    {
        ULONGLONG total_memory;
        ULONGLONG available_memory;
        ULONGLONG used_memory;
        double memory_usage_percent;
    };

    struct CpuUsage
    {
        double cpu_usage_percent;
    };

    class SystemPerformanceMonitor
    {
    public:
        static auto GetMemoryUsage() -> MemoryUsage;
        static auto GetCpuUsage(int interval = 1) -> CpuUsage;
    };
}
