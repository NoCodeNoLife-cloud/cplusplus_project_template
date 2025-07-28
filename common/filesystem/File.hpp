#pragma once
#include <chrono>
#include <filesystem>
#include <string>

namespace common {
class File final {
 public:
  explicit File(const std::string& path);
  explicit File(std::filesystem::path path);
  explicit File(const char* path);
  ~File();
  [[nodiscard]] auto canExecute() const -> bool;
  [[nodiscard]] auto canRead() const -> bool;
  [[nodiscard]] auto canWrite() const -> bool;
  [[nodiscard]] auto createNewFile() const -> bool;
  [[nodiscard]] auto deleteFile() const -> bool;
  [[nodiscard]] auto exists() const -> bool;
  [[nodiscard]] auto getAbsolutePath() const -> std::string;
  [[nodiscard]] auto getAbsoluteFile() const -> File;
  [[nodiscard]] auto getName() const -> std::string;
  [[nodiscard]] auto getParent() const -> std::string;
  [[nodiscard]] auto getParentFile() const -> File;
  [[nodiscard]] auto getPath() const -> std::string;
  [[nodiscard]] auto getTotalSpace() const -> int64_t;
  [[nodiscard]] auto getUsableSpace() const -> int64_t;
  [[nodiscard]] auto hashCode() const -> size_t;
  [[nodiscard]] auto isAbsolute() const -> bool;
  [[nodiscard]] auto renameTo(const File& dest) const -> bool;
  [[nodiscard]] auto isFile() const -> bool;
  [[nodiscard]] auto isHidden() const -> bool;
  [[nodiscard]] auto length() const -> int64_t;
  [[nodiscard]] auto lastModified() const -> int64_t;
  [[nodiscard]] auto toURI() const -> std::string;
  static auto printFilesWithDepth(const std::filesystem::path& file_path)
      -> void;
  static auto getFileMD5(const std::filesystem::path& filePath) -> std::string;

 private:
  std::filesystem::path file_path_;
};
}  // namespace common
