#pragma once
#include <chrono>
#include <filesystem>
#include <string>

namespace common {
/// @brief A class representing a file in the file system
/// This class provides various operations that can be performed on files,
/// such as checking permissions, creating, deleting, renaming, and retrieving
/// file properties like size, modification time, and path information.
class File final {
 public:
  explicit File(const std::string& path);
  explicit File(std::filesystem::path path);
  explicit File(const char* path);
  ~File();

  /// @brief Checks if the file can be executed
  /// @return true if the file can be executed, false otherwise
  [[nodiscard]] auto canExecute() const -> bool;

  /// @brief Checks if the file can be read
  /// @return true if the file can be read, false otherwise
  [[nodiscard]] auto canRead() const -> bool;

  /// @brief Checks if the file can be written to
  /// @return true if the file can be written to, false otherwise
  [[nodiscard]] auto canWrite() const -> bool;

  /// @brief Creates a new file
  /// @return true if the file was created successfully, false otherwise
  [[nodiscard]] auto createNewFile() const -> bool;

  /// @brief Deletes the file
  /// @return true if the file was deleted successfully, false otherwise
  [[nodiscard]] auto deleteFile() const -> bool;

  /// @brief Checks if the file exists
  /// @return true if the file exists, false otherwise
  [[nodiscard]] auto exists() const -> bool;

  /// @brief Gets the absolute path of the file
  /// @return The absolute path as a string
  [[nodiscard]] auto getAbsolutePath() const -> std::string;

  /// @brief Gets the absolute file object
  /// @return A File object representing the absolute path
  [[nodiscard]] auto getAbsoluteFile() const -> File;

  /// @brief Gets the name of the file
  /// @return The file name as a string
  [[nodiscard]] auto getName() const -> std::string;

  /// @brief Gets the parent directory path
  /// @return The parent directory path as a string
  [[nodiscard]] auto getParent() const -> std::string;

  /// @brief Gets the parent directory as a File object
  /// @return A File object representing the parent directory
  [[nodiscard]] auto getParentFile() const -> File;

  /// @brief Gets the file path
  /// @return The file path as a string
  [[nodiscard]] auto getPath() const -> std::string;

  /// @brief Gets the total space of the file system
  /// @return The total space in bytes
  [[nodiscard]] auto getTotalSpace() const -> int64_t;

  /// @brief Gets the usable space of the file system
  /// @return The usable space in bytes
  [[nodiscard]] auto getUsableSpace() const -> int64_t;

  /// @brief Gets the hash code of the file path
  /// @return The hash code as a size_t
  [[nodiscard]] auto hashCode() const -> size_t;

  /// @brief Checks if the file path is absolute
  /// @return true if the path is absolute, false otherwise
  [[nodiscard]] auto isAbsolute() const -> bool;

  /// @brief Renames the file to the destination file
  /// @param dest The destination file
  /// @return true if the file was renamed successfully, false otherwise
  [[nodiscard]] auto renameTo(const File& dest) const -> bool;

  /// @brief Checks if the path refers to a regular file
  /// @return true if it's a regular file, false otherwise
  [[nodiscard]] auto isFile() const -> bool;

  /// @brief Checks if the file is hidden
  /// @return true if the file is hidden, false otherwise
  [[nodiscard]] auto isHidden() const -> bool;

  /// @brief Gets the length of the file
  /// @return The file length in bytes
  [[nodiscard]] auto length() const -> int64_t;

  /// @brief Gets the last modified time of the file
  /// @return The last modified time as a timestamp
  [[nodiscard]] auto lastModified() const -> int64_t;

  /// @brief Converts the file path to a URI string
  /// @return The URI as a string
  [[nodiscard]] auto toURI() const -> std::string;

  /// @brief Prints files with depth information
  /// @param file_path The path to start printing from
  static auto printFilesWithDepth(const std::filesystem::path& file_path) -> void;

  /// @brief Gets the MD5 hash of a file
  /// @param filePath The path to the file
  /// @return The MD5 hash as a string
  static auto getFileMD5(const std::filesystem::path& filePath) -> std::string;

 private:
  std::filesystem::path file_path_;
};
}  // namespace common
