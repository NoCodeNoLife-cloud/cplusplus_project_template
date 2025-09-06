#pragma once
#include <string>
#include <vector>

namespace fox {
/// @brief A utility class for retrieving system hardware and OS information.
/// The SystemInfo class provides static methods to fetch various system details
/// such as CPU model, memory information, OS version, motherboard details,
/// graphics card info, disk drives, and BIOS information.
struct MotherboardInfo {
  std::string manufacturer;
  std::string model;
  std::string biosVersion;
  std::string systemSerial;
};

/// @brief A utility class for retrieving system hardware and OS information.
/// The SystemInfo class provides static methods to fetch various system details
/// such as CPU model, memory information, OS version, motherboard details,
/// graphics card info, disk drives, and BIOS information.
class SystemInfo {
 public:
  /// @brief Get CPU model from registry
  /// @return CPU model as string
  static auto GetCpuModelFromRegistry() -> std::string;

  /// @brief Get memory details
  /// @return Memory details as string
  static auto GetMemoryDetails() -> std::string;

  /// @brief Get OS version
  /// @return OS version as string
  static auto GetOSVersion() -> std::string;

  /// @brief Get motherboard information
  /// @return MotherboardInfo struct
  static auto GetMotherboardInfo() -> MotherboardInfo;

  /// @brief Get graphics card information
  /// @return Graphics card info as string
  static auto GetGraphicsCardInfo() -> std::string;

  /// @brief Get disk drive information
  /// @return Vector of disk drive info strings
  static auto GetDiskDriveInfo() -> std::vector<std::string>;

  /// @brief Get BIOS information
  /// @return Vector of BIOS info strings
  static auto GetBIOSInfo() -> std::vector<std::string>;
};
}  // namespace fox
