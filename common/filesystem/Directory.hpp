#pragma once
#include <filesystem>

namespace common {
class Directory {
 public:
  explicit Directory(std::filesystem::path filePath);
  [[nodiscard]] auto mkdir() const -> bool;
  [[nodiscard]] auto exists() const -> bool;
  [[nodiscard]] auto isDirectory() const -> bool;
  [[nodiscard]] auto listDir(bool recursive) const
      -> std::vector<std::filesystem::directory_entry>;
  [[nodiscard]] static auto listDir(const std::filesystem::path& dir_path,
                                    bool recursive)
      -> std::vector<std::filesystem::directory_entry>;
  [[nodiscard]] auto mkdirs() const -> bool;
  [[nodiscard]] auto remove() const -> bool;
  [[nodiscard]] auto removeAll() const -> std::uintmax_t;
  [[nodiscard]] auto copy(const std::filesystem::path& destination) const
      -> bool;
  [[nodiscard]] auto move(const std::filesystem::path& destination) const
      -> bool;
  [[nodiscard]] auto size() const -> std::uintmax_t;
  [[nodiscard]] auto lastModifiedTime() const
      -> std::optional<std::chrono::system_clock::time_point>;
  [[nodiscard]] auto isEmpty() const -> bool;
  [[nodiscard]] auto listEntries(bool recursive = false) const
      -> std::vector<std::filesystem::directory_entry>;
  [[nodiscard]] auto clearAll() const -> bool;
  static auto getCurrentWorkingDirectory() -> std::filesystem::path;

 private:
  std::filesystem::path dir_path_;
};
}  // namespace common
