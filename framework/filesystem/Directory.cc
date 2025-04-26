#include "Directory.hpp"
#include <utility>

namespace framework::filesystem {
  Directory::Directory(std::filesystem::path filePath): file_path_(std::move(filePath)) {}

  auto Directory::mkdir() const -> bool {
    return create_directory(file_path_);
  }

  auto Directory::exists() const -> bool {
    return std::filesystem::is_directory(file_path_);
  }

  auto Directory::isDirectory() const -> bool {
    return std::filesystem::is_directory(file_path_);
  }

  auto Directory::list() const -> std::vector<std::string> {
    std::vector<std::string> entries;
    if (isDirectory()) {
      for (const auto& entry : std::filesystem::directory_iterator(file_path_)) {
        entries.push_back(entry.path().filename().string());
      }
    }
    return entries;
  }
}
