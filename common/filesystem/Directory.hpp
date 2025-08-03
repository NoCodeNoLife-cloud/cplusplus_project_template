#pragma once
#include <filesystem>

namespace common {
class Directory {
 public:
  explicit Directory(std::filesystem::path filePath);

  /// @brief Create a directory
  /// @return true if the directory was created successfully, false otherwise
  [[nodiscard]] auto mkdir() const -> bool;

  /// @brief Create directories recursively
  /// @param exist_ok If true, no error will be thrown if the directory already exists
  /// @return true if the directories were created successfully, false otherwise
  [[nodiscard]] auto mkdirs(bool exist_ok = false) const -> bool;

  /// @brief Check if the directory exists
  /// @return true if the directory exists, false otherwise
  [[nodiscard]] auto exists() const -> bool;

  /// @brief Check if the path is a directory
  /// @return true if the path is a directory, false otherwise
  [[nodiscard]] auto isDirectory() const -> bool;

  /// @brief List directory contents
  /// @param recursive Whether to list subdirectories recursively
  /// @return A vector of directory entries
  [[nodiscard]] auto listDir(bool recursive) const -> std::vector<std::filesystem::directory_entry>;

  /// @brief List directory contents
  /// @param dir_path The directory path to list
  /// @param recursive Whether to list subdirectories recursively
  /// @return A vector of directory entries
  [[nodiscard]] static auto listDir(const std::filesystem::path& dir_path, bool recursive) -> std::vector<std::filesystem::directory_entry>;

  /// @brief Create directories recursively
  /// @return true if the directories were created successfully, false otherwise
  [[nodiscard]] auto mkdirs() const -> bool;

  /// @brief Remove the directory
  /// @return true if the directory was removed successfully, false otherwise
  [[nodiscard]] auto remove() const -> bool;

  /// @brief Remove the directory and all its contents
  /// @return The number of files removed
  [[nodiscard]] auto removeAll() const -> std::uintmax_t;

  /// @brief Copy the directory to a destination
  /// @param destination The destination path
  /// @return true if the directory was copied successfully, false otherwise
  [[nodiscard]] auto copy(const std::filesystem::path& destination) const -> bool;

  /// @brief Move the directory to a destination
  /// @param destination The destination path
  /// @return true if the directory was moved successfully, false otherwise
  [[nodiscard]] auto move(const std::filesystem::path& destination) const -> bool;

  /// @brief Get the size of the directory
  /// @return The size of the directory in bytes
  [[nodiscard]] auto size() const -> std::uintmax_t;

  /// @brief Get the last modified time of the directory
  /// @return The last modified time, or std::nullopt if an error occurred
  [[nodiscard]] auto lastModifiedTime() const -> std::optional<std::chrono::system_clock::time_point>;

  /// @brief Check if the directory is empty
  /// @return true if the directory is empty, false otherwise
  [[nodiscard]] auto isEmpty() const -> bool;

  /// @brief List directory entries
  /// @param recursive Whether to list subdirectories recursively
  /// @return A vector of directory entries
  [[nodiscard]] auto listEntries(bool recursive = false) const -> std::vector<std::filesystem::directory_entry>;

  /// @brief Clear all contents of the directory
  /// @return true if the directory was cleared successfully, false otherwise
  [[nodiscard]] auto clearAll() const -> bool;

  /// @brief Get the current working directory
  /// @return The current working directory path
  static auto getCurrentWorkingDirectory() -> std::filesystem::path;

 private:
  std::filesystem::path dir_path_;
};
}  // namespace common
