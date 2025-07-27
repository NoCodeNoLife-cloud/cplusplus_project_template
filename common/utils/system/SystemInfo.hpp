#pragma once
#include <string>
#include <vector>
#include <windows.h>

namespace common
{
    struct MotherboardInfo
    {
        std::string manufacturer;
        std::string model;
        std::string biosVersion;
        std::string systemSerial;
    };

    class SystemInfo
    {
    public:
        static auto GetCpuModelFromRegistry() -> std::string;
        static auto GetMemoryDetails() -> std::string;
        static auto GetOSVersion() -> std::string;
        static auto GetMotherboardInfo() -> MotherboardInfo;
        static auto GetGraphicsCardInfo() -> std::string;
        static auto GetDiskDriveInfo() -> std::vector<std::string>;
        static auto GetBIOSInfo() -> std::vector<std::string>;
    };
}
