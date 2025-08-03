#pragma once
#include <windows.h>

namespace common {
struct MemoryUsage {
  ULONGLONG total_memory;
  ULONGLONG available_memory;
  ULONGLONG used_memory;
  double memory_usage_percent;
};

struct CpuUsage {
  double cpu_usage_percent;
};

class SystemPerformanceMonitor {
 public:
  /// @brief Get the current memory usage of the system
  /// @return MemoryUsage struct containing total, available, used memory and usage percentage
  static auto GetMemoryUsage() -> MemoryUsage;

  /// @brief Get the current CPU usage of the system
  /// @param interval Time interval in seconds for measuring CPU usage, default is 1 second
  /// @return CpuUsage struct containing CPU usage percentage
  static auto GetCpuUsage(int interval = 1) -> CpuUsage;
};
}  // namespace common
