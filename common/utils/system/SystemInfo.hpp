#pragma once
#include <windows.h>

#include <string>
#include <vector>

namespace fox
{
/// @brief A utility class for retrieving system hardware and OS information.
/// The SystemInfo class provides static methods to fetch various system details
/// such as CPU model, memory information, OS version, motherboard details,
/// graphics card info, disk drives, and BIOS information.
struct MotherboardInfo
{
    std::string manufacturer;
    std::string model;
    std::string biosVersion;
    std::string systemSerial;
};

/// @brief A utility class for retrieving system hardware and OS information.
/// The SystemInfo class provides static methods to fetch various system details
/// such as CPU model, memory information, OS version, motherboard details,
/// graphics card info, disk drives, and BIOS information.
class SystemInfo
{
  public:
    /// @brief Get CPU model from registry
    /// @return CPU model as string
    static auto GetCpuModelFromRegistry() -> std::string
    {
        HKEY hKey;

        if (LONG regResult = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0,
                                           KEY_READ, &hKey);
            regResult == ERROR_SUCCESS)
        {
            wchar_t cpuName[256];
            DWORD size = sizeof(cpuName);
            regResult = RegQueryValueExW(hKey, L"ProcessorNameString", nullptr, nullptr,
                                         reinterpret_cast<LPBYTE>(cpuName), &size);
            RegCloseKey(hKey);

            if (regResult == ERROR_SUCCESS)
            {
                if (const int32_t len = WideCharToMultiByte(CP_UTF8, 0, cpuName, -1, nullptr, 0, nullptr, nullptr);
                    len > 0)
                {
                    std::string cpuModel(len - 1,
                                         0); // len includes null terminator, so subtract 1
                    WideCharToMultiByte(CP_UTF8, 0, cpuName, -1, &cpuModel[0], len, nullptr, nullptr);
                    return cpuModel;
                }
            }
        }
        return "Unknown CPU Model";
    }

    /// @brief Get memory details
    /// @return Memory details as string
    static auto GetMemoryDetails() -> std::string
    {
        HKEY hKey;
        std::string result;

        const LONG resultReg = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                                             L"SYSTEM\\CurrentControlSet\\Control\\Class\\{4D36E965-"
                                             L"E325-11CE-BFC1-08002BE10318}",
                                             0, KEY_READ, &hKey);

        if (resultReg == ERROR_SUCCESS)
        {
            wchar_t memInfo[256];
            DWORD size = sizeof(memInfo);

            if (RegQueryValueExW(hKey, L"DeviceDesc", nullptr, nullptr, reinterpret_cast<LPBYTE>(memInfo), &size) ==
                ERROR_SUCCESS)
            {
                if (const int32_t len = WideCharToMultiByte(CP_UTF8, 0, memInfo, -1, nullptr, 0, nullptr, nullptr);
                    len > 0)
                {
                    result.resize(len - 1); // len includes null terminator, so subtract 1
                    WideCharToMultiByte(CP_UTF8, 0, memInfo, -1, &result[0], len, nullptr, nullptr);
                }
            }

            RegCloseKey(hKey);
        }

        return result.empty() ? "Memory details not available" : result;
    }

    /// @brief Get OS version
    /// @return OS version as string
    static auto GetOSVersion() -> std::string
    {
        HKEY hKey;
        std::string result;

        const LONG lResult =
            RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0, KEY_READ, &hKey);

        if (lResult == ERROR_SUCCESS)
        {
            wchar_t osInfo[256];
            DWORD size = sizeof(osInfo);

            if (RegQueryValueExW(hKey, L"ProductName", nullptr, nullptr, reinterpret_cast<LPBYTE>(osInfo), &size) ==
                ERROR_SUCCESS)
            {
                if (const int32_t len = WideCharToMultiByte(CP_UTF8, 0, osInfo, -1, nullptr, 0, nullptr, nullptr);
                    len > 0)
                {
                    result.resize(len - 1); // len includes null terminator, so subtract 1
                    WideCharToMultiByte(CP_UTF8, 0, osInfo, -1, &result[0], len, nullptr, nullptr);
                }

                wchar_t buildNum[64];
                size = sizeof(buildNum);
                if (RegQueryValueExW(hKey, L"CurrentBuildNumber", nullptr, nullptr, reinterpret_cast<LPBYTE>(buildNum),
                                     &size) == ERROR_SUCCESS)
                {
                    if (const int32_t buildLen =
                            WideCharToMultiByte(CP_UTF8, 0, buildNum, -1, nullptr, 0, nullptr, nullptr);
                        buildLen > 0)
                    {
                        char buildStr[64];
                        WideCharToMultiByte(CP_UTF8, 0, buildNum, -1, buildStr, sizeof(buildStr), nullptr, nullptr);
                        result += " (Build ";
                        result += buildStr;
                        result += ")";
                    }
                }
            }

            RegCloseKey(hKey);
        }

        return result.empty() ? "Windows OS Information Not Available" : result;
    }

    /// @brief Get motherboard information
    /// @return MotherboardInfo struct
    static auto GetMotherboardInfo() -> MotherboardInfo
    {
        MotherboardInfo info;
        HKEY hKey;

        LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"HARDWARE\\DESCRIPTION\\System\\BIOS", 0, KEY_READ, &hKey);

        if (result == ERROR_SUCCESS)
        {
            wchar_t buffer[256];
            DWORD size;
            size = sizeof(buffer);

            if (RegQueryValueExW(hKey, L"BaseBoardManufacturer", nullptr, nullptr, reinterpret_cast<LPBYTE>(buffer),
                                 &size) == ERROR_SUCCESS)
            {
                if (const int32_t len = WideCharToMultiByte(CP_UTF8, 0, buffer, -1, nullptr, 0, nullptr, nullptr);
                    len > 0)
                {
                    info.manufacturer.resize(len - 1); // len includes null terminator, so subtract 1
                    WideCharToMultiByte(CP_UTF8, 0, buffer, -1, &info.manufacturer[0], len, nullptr, nullptr);
                }
            }

            size = sizeof(buffer);
            if (RegQueryValueExW(hKey, L"BaseBoardProduct", nullptr, nullptr, reinterpret_cast<LPBYTE>(buffer),
                                 &size) == ERROR_SUCCESS)
            {
                if (const int32_t len = WideCharToMultiByte(CP_UTF8, 0, buffer, -1, nullptr, 0, nullptr, nullptr);
                    len > 0)
                {
                    info.model.resize(len - 1); // len includes null terminator, so subtract 1
                    WideCharToMultiByte(CP_UTF8, 0, buffer, -1, &info.model[0], len, nullptr, nullptr);
                }
            }

            size = sizeof(buffer);
            if (RegQueryValueExW(hKey, L"BiosVersion", nullptr, nullptr, reinterpret_cast<LPBYTE>(buffer), &size) ==
                ERROR_SUCCESS)
            {
                if (const int32_t len = WideCharToMultiByte(CP_UTF8, 0, buffer, -1, nullptr, 0, nullptr, nullptr);
                    len > 0)
                {
                    info.biosVersion.resize(len - 1); // len includes null terminator, so subtract 1
                    WideCharToMultiByte(CP_UTF8, 0, buffer, -1, &info.biosVersion[0], len, nullptr, nullptr);
                }
            }

            RegCloseKey(hKey);
        }

        result =
            RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0, KEY_READ, &hKey);

        if (result == ERROR_SUCCESS)
        {
            wchar_t buffer[256];
            DWORD size = sizeof(buffer);

            if (RegQueryValueExW(hKey, L"SystemSerialNumber", nullptr, nullptr, reinterpret_cast<LPBYTE>(buffer),
                                 &size) == ERROR_SUCCESS ||
                RegQueryValueExW(hKey, L"ProductId", nullptr, nullptr, reinterpret_cast<LPBYTE>(buffer), &size) ==
                    ERROR_SUCCESS)
            {
                if (const int32_t len = WideCharToMultiByte(CP_UTF8, 0, buffer, -1, nullptr, 0, nullptr, nullptr);
                    len > 0)
                {
                    info.systemSerial.resize(len - 1); // len includes null terminator, so subtract 1
                    WideCharToMultiByte(CP_UTF8, 0, buffer, -1, &info.systemSerial[0], len, nullptr, nullptr);
                }
            }

            RegCloseKey(hKey);
        }

        return info;
    }

    /// @brief Get graphics card information
    /// @return Graphics card info as string
    static auto GetGraphicsCardInfo() -> std::string
    {
        HKEY hKey;
        std::string result;

        const LONG resultReg = RegOpenKeyExW(
            HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\GraphicsDrivers\\Devices", 0, KEY_READ, &hKey);

        if (resultReg == ERROR_SUCCESS)
        {
            wchar_t subKeyName[256];
            DWORD subKeySize = sizeof(subKeyName) / sizeof(wchar_t);
            FILETIME lastWriteTime;

            if (RegEnumKeyExW(hKey, 0, subKeyName, &subKeySize, nullptr, nullptr, nullptr, &lastWriteTime) ==
                ERROR_SUCCESS)
            {
                HKEY hSubKey;
                if (RegOpenKeyExW(hKey, subKeyName, 0, KEY_READ, &hSubKey) == ERROR_SUCCESS)
                {
                    wchar_t deviceDesc[256];
                    DWORD size = sizeof(deviceDesc);

                    if (RegQueryValueExW(hSubKey, L"DeviceDesc", nullptr, nullptr, reinterpret_cast<LPBYTE>(deviceDesc),
                                         &size) == ERROR_SUCCESS)
                    {
                        if (const int32_t len =
                                WideCharToMultiByte(CP_UTF8, 0, deviceDesc, -1, nullptr, 0, nullptr, nullptr);
                            len > 0)
                        {
                            result.resize(len - 1); // len includes null terminator, so subtract 1
                            WideCharToMultiByte(CP_UTF8, 0, deviceDesc, -1, &result[0], len, nullptr, nullptr);
                        }
                    }

                    RegCloseKey(hSubKey);
                }
            }

            RegCloseKey(hKey);
        }

        return result.empty() ? "Graphics card information not available" : result;
    }

    /// @brief Get disk drive information
    /// @return Vector of disk drive info strings
    static auto GetDiskDriveInfo() -> std::vector<std::string>
    {
        std::vector<std::string> drives;
        HKEY hKey;

        const LONG result =
            RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Services\\Disk\\Enum", 0, KEY_READ, &hKey);

        if (result == ERROR_SUCCESS)
        {
            wchar_t valueName[256];
            wchar_t valueData[512];
            DWORD valueNameSize = sizeof(valueName) / sizeof(wchar_t);
            DWORD valueDataSize = sizeof(valueData);
            DWORD index = 0;

            while (RegEnumValueW(hKey, index++, valueName, &valueNameSize, nullptr, nullptr,
                                 reinterpret_cast<LPBYTE>(valueData), &valueDataSize) == ERROR_SUCCESS)
            {
                if (wcscmp(valueName, L"0") != 0)
                {
                    if (const int32_t len =
                            WideCharToMultiByte(CP_UTF8, 0, valueData, -1, nullptr, 0, nullptr, nullptr);
                        len > 0)
                    {
                        std::string driveInfo(len - 1, 0); // len includes null terminator, so subtract 1
                        WideCharToMultiByte(CP_UTF8, 0, valueData, -1, &driveInfo[0], len, nullptr, nullptr);
                        drives.emplace_back(std::move(driveInfo));
                    }
                }

                valueNameSize = sizeof(valueName) / sizeof(wchar_t);
                valueDataSize = sizeof(valueData);
            }

            RegCloseKey(hKey);
        }

        return drives;
    }

    /// @brief Get BIOS information
    /// @return Vector of BIOS info strings
    static auto GetBIOSInfo() -> std::vector<std::string>
    {
        std::vector<std::string> adapters;
        HKEY hKey;

        const LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                                          L"SYSTEM\\CurrentControlSet\\Control\\Class"
                                          L"\\{4D36E972-E325-11CE-BFC1-08002BE10318}",
                                          0, KEY_READ, &hKey);

        if (result == ERROR_SUCCESS)
        {
            DWORD index = 0;
            wchar_t subKeyName[256];
            DWORD subKeySize = sizeof(subKeyName) / sizeof(wchar_t);

            while (RegEnumKeyExW(hKey, index++, subKeyName, &subKeySize, nullptr, nullptr, nullptr, nullptr) ==
                   ERROR_SUCCESS)
            {
                if (iswdigit(subKeyName[0]))
                {
                    HKEY hSubKey;
                    if (RegOpenKeyExW(hKey, subKeyName, 0, KEY_READ, &hSubKey) == ERROR_SUCCESS)
                    {
                        wchar_t adapterName[256];
                        DWORD size = sizeof(adapterName);

                        if (RegQueryValueExW(hSubKey, L"DriverDesc", nullptr, nullptr,
                                             reinterpret_cast<LPBYTE>(adapterName), &size) == ERROR_SUCCESS)
                        {
                            if (const int32_t len =
                                    WideCharToMultiByte(CP_UTF8, 0, adapterName, -1, nullptr, 0, nullptr, nullptr);
                                len > 0)
                            {
                                std::string name(len - 1, 0); // len includes null terminator, so subtract 1
                                WideCharToMultiByte(CP_UTF8, 0, adapterName, -1, &name[0], len, nullptr, nullptr);
                                adapters.emplace_back(std::move(name));
                            }
                        }

                        RegCloseKey(hSubKey);
                    }
                }

                subKeySize = sizeof(subKeyName) / sizeof(wchar_t);
            }

            RegCloseKey(hKey);
        }

        return adapters;
    }
};
} // namespace fox