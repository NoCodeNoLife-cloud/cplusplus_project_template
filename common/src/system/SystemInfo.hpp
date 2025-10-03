#pragma once
#include <string>
#include <vector>

namespace common
{
    /// @brief Structure to hold motherboard information
    struct MotherboardInfo
    {
        std::string manufacturer{};
        std::string model{};
        std::string biosVersion{};
        std::string systemSerial{};
    };

    /// @brief A utility class for retrieving system hardware and OS information.
    /// The SystemInfo class provides static methods to fetch various system details
    /// such as CPU model, memory information, OS version, motherboard details,
    /// graphics card info, disk drives, and BIOS information.
    class SystemInfo
    {
    public:
        SystemInfo() = delete;

        /// @brief Get CPU model from registry
        /// @return CPU model as string
        [[nodiscard]] static auto GetCpuModelFromRegistry() noexcept -> std::string;

        /// @brief Get memory details
        /// @return Memory details as string
        [[nodiscard]] static auto GetMemoryDetails() noexcept -> std::string;

        /// @brief Get OS version
        /// @return OS version as string
        [[nodiscard]] static auto GetOSVersion() noexcept -> std::string;

        /// @brief Get motherboard information
        /// @return MotherboardInfo struct
        [[nodiscard]] static auto GetMotherboardInfo() noexcept -> MotherboardInfo;

        /// @brief Get graphics card information
        /// @return Graphics card info as string
        [[nodiscard]] static auto GetGraphicsCardInfo() noexcept -> std::string;

        /// @brief Get disk drive information
        /// @return Vector of disk drive info strings
        [[nodiscard]] static auto GetDiskDriveInfo() noexcept -> std::vector<std::string>;

        /// @brief Get BIOS information
        /// @return Vector of BIOS info strings
        [[nodiscard]] static auto GetBIOSInfo() noexcept -> std::vector<std::string>;
    };
}
