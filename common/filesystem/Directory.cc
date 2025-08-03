#include "Directory.hpp"

#include <queue>
#include <utility>

namespace common {
Directory::Directory(std::filesystem::path filePath) : dir_path_(std::move(filePath)) {}

auto Directory::mkdir() const -> bool {
  try {
    return std::filesystem::create_directory(dir_path_);
  } catch (...) {
    return false;
  }
}

auto Directory::mkdirs(const bool exist_ok) const -> bool {
  try {
    if (exist_ok) {
      return std::filesystem::create_directories(dir_path_);
    }
    // Check if any part of the path already exists
    if (std::filesystem::exists(dir_path_)) {
      return false;
    }
    // For parent directories, we need to check recursively
    auto parent = dir_path_.parent_path();
    while (!parent.empty() && parent != dir_path_.root_path()) {
      if (std::filesystem::exists(parent) && !std::filesystem::is_directory(parent)) {
        return false;
      }
      parent = parent.parent_path();
    }
    return std::filesystem::create_directories(dir_path_);
  } catch (...) {
    return false;
  }
}

auto Directory::exists() const -> bool { return std::filesystem::exists(dir_path_); }

auto Directory::isDirectory() const -> bool { return std::filesystem::is_directory(dir_path_); }

auto Directory::mkdirs() const -> bool {
  try {
    return std::filesystem::create_directories(dir_path_);
  } catch (...) {
    return false;
  }
}

auto Directory::remove() const -> bool {
  try {
    return std::filesystem::remove(dir_path_);
  } catch (...) {
    return false;
  }
}

auto Directory::removeAll() const -> std::uintmax_t {
  try {
    return std::filesystem::remove_all(dir_path_);
  } catch (...) {
    return 0;
  }
}

auto Directory::copy(const std::filesystem::path& destination) const -> bool {
  try {
    if (!exists() || !isDirectory()) return false;

    if (!std::filesystem::create_directories(destination)) {
      return false;
    }

    std::queue<std::pair<std::filesystem::path, std::filesystem::path>> dirQueue;
    dirQueue.emplace(dir_path_, destination);

    while (!dirQueue.empty()) {
      auto [srcPath, dstPath] = dirQueue.front();
      dirQueue.pop();

      for (const auto& entry : std::filesystem::directory_iterator(srcPath)) {
        auto entryPath = entry.path();
        auto relativePath = entryPath.lexically_relative(srcPath);
        auto targetPath = dstPath / relativePath;

        if (entry.is_directory()) {
          if (!std::filesystem::create_directory(targetPath)) {
            return false;
          }
          dirQueue.emplace(entryPath, targetPath);
        } else if (entry.is_regular_file()) {
          std::filesystem::copy_file(entryPath, targetPath, std::filesystem::copy_options::overwrite_existing);
        }
      }
    }
    return true;
  } catch (...) {
    return false;
  }
}

auto Directory::move(const std::filesystem::path& destination) const -> bool {
  try {
    std::filesystem::rename(dir_path_, destination);
    return true;
  } catch (...) {
    return false;
  }
}

auto Directory::size() const -> std::uintmax_t {
  std::uintmax_t total = 0;
  try {
    for (const auto& entry : std::filesystem::recursive_directory_iterator(dir_path_)) {
      if (entry.is_regular_file()) {
        total += entry.file_size();
      }
    }
  } catch (...) {
  }
  return total;
}

auto Directory::lastModifiedTime() const -> std::optional<std::chrono::system_clock::time_point> {
  try {
    const auto ftime = std::filesystem::last_write_time(dir_path_);
    return std::chrono::clock_cast<std::chrono::system_clock>(ftime);
  } catch (...) {
    return std::nullopt;
  }
}

auto Directory::isEmpty() const -> bool {
  try {
    return std::filesystem::is_empty(dir_path_);
  } catch (...) {
    return false;
  }
}

auto Directory::listDir(const bool recursive = false) const -> std::vector<std::filesystem::directory_entry> { return listDir(dir_path_, recursive); }
auto Directory::listDir(const std::filesystem::path& dir_path, const bool recursive = false) -> std::vector<std::filesystem::directory_entry> {
  std::vector<std::filesystem::directory_entry> entries;
  try {
    if (recursive) {
      for (const auto& entry : std::filesystem::recursive_directory_iterator(dir_path)) {
        entries.push_back(entry);
      }
    } else {
      for (const auto& entry : std::filesystem::directory_iterator(dir_path)) {
        entries.push_back(entry);
      }
    }
  } catch (...) {
  }
  return entries;
}

auto Directory::listEntries(const bool recursive) const -> std::vector<std::filesystem::directory_entry> { return listDir(dir_path_, recursive); }

auto Directory::clearAll() const -> bool {
  try {
    if (!std::filesystem::exists(dir_path_) || !std::filesystem::is_directory(dir_path_)) {
      return false;
    }
    for (const auto& entry : std::filesystem::directory_iterator(dir_path_)) {
      std::filesystem::remove_all(entry.path());
    }
    return true;
  } catch (...) {
    return false;
  }
}

auto Directory::getCurrentWorkingDirectory() -> std::filesystem::path { return std::filesystem::current_path(); }
}  // namespace common
