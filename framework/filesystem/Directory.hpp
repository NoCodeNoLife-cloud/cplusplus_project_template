#pragma once
#include <filesystem>

namespace framework::filesystem {
  class Directory {
  public:
    explicit Directory(std::filesystem::path filePath);
    [[nodiscard]] auto mkdir() const -> bool;
    [[nodiscard]] auto exists() const -> bool;
    [[nodiscard]] auto isDirectory() const -> bool;
    [[nodiscard]] auto list() const -> std::vector<std::string> ;

  private:
    std::filesystem::path file_path_;
  };
} // namespace framework::filesystem
