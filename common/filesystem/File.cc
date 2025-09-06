#include "File.hpp"

#include <openssl/evp.h>
#include <windows.h>

#include <array>
#include <fstream>
#include <iostream>

namespace fox {
File::File(const std::string& path) : file_path_(path) {}

File::File(std::filesystem::path path) : file_path_(std::move(path)) {}

File::File(const char* path) : file_path_(path) {}

File::~File() = default;

auto File::canExecute() const -> bool {
  const DWORD attributes = GetFileAttributesW(file_path_.c_str());
  return attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY) == 0;
}

auto File::canRead() const -> bool {
  const std::ifstream file(file_path_);
  return file.good();
}

auto File::canWrite() const -> bool {
  const std::ofstream file(file_path_, std::ios::app);
  return file.good();
}

auto File::createNewFile() const -> bool {
  if (std::filesystem::exists(file_path_)) {
    return false;
  }
  const std::ofstream file(file_path_);
  return file.good();
}

auto File::deleteFile() const -> bool { return std::filesystem::remove(file_path_); }

auto File::exists() const -> bool { return std::filesystem::exists(file_path_); }

auto File::getAbsolutePath() const -> std::string { return absolute(file_path_).string(); }

auto File::getAbsoluteFile() const -> File { return File(absolute(file_path_).string()); }

auto File::getName() const -> std::string { return file_path_.filename().string(); }

auto File::getParent() const -> std::string { return file_path_.parent_path().string(); }

auto File::getParentFile() const -> File { return file_path_.has_parent_path() ? File(file_path_.parent_path()) : File(std::string("")); }

auto File::getPath() const -> std::string { return file_path_.string(); }

auto File::getTotalSpace() const -> int64_t {
  const auto spaceInfo = space(file_path_);
  return static_cast<int64_t>(spaceInfo.capacity);
}

auto File::getUsableSpace() const -> int64_t {
  const auto spaceInfo = space(file_path_);
  return static_cast<int64_t>(spaceInfo.free);
}

auto File::hashCode() const -> size_t { return std::hash<std::string>()(file_path_.string()); }

auto File::isAbsolute() const -> bool { return file_path_.is_absolute(); }

auto File::renameTo(const File& dest) const -> bool {
  try {
    std::filesystem::rename(file_path_, dest.file_path_);
    return true;
  } catch (const std::filesystem::filesystem_error&) {
    return false;
  }
}

auto File::isFile() const -> bool { return is_regular_file(file_path_); }

auto File::isHidden() const -> bool {
  const DWORD attributes = GetFileAttributesW(file_path_.c_str());
  return attributes != INVALID_FILE_ATTRIBUTES && attributes & FILE_ATTRIBUTE_HIDDEN;
}

auto File::length() const -> int64_t {
  if (std::filesystem::exists(file_path_) && is_regular_file(file_path_)) {
    return static_cast<int64_t>(file_size(file_path_));
  }
  return 0;
}

auto File::lastModified() const -> int64_t {
  const auto lastWriteTime = last_write_time(file_path_);
  const auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(lastWriteTime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());
  return std::chrono::system_clock::to_time_t(sctp);
}

auto File::toURI() const -> std::string { return "file://" + file_path_.string(); }

auto File::printFilesWithDepth(const std::filesystem::path& file_path) -> void {
  if (!std::filesystem::exists(file_path) || !std::filesystem::is_directory(file_path)) {
    throw std::runtime_error("Invalid directory path: " + file_path.string());
  }

  for (auto it_entry = std::filesystem::recursive_directory_iterator(file_path); it_entry != std::filesystem::recursive_directory_iterator{}; ++it_entry) {
    const auto& entry = *it_entry;
    const auto depth = it_entry.depth();

    std::cout << std::string(depth * 2, ' ');

    if (entry.is_directory()) {
      std::cout << "[DIR]" << entry.path().filename() << std::endl;
    } else {
      std::cout << "[FILE]" << entry.path().filename() << std::endl;
    }
  }
}

auto File::getFileMD5(const std::filesystem::path& filePath) -> std::string {
  std::ifstream file(filePath, std::ios::binary);
  if (!file) {
    throw std::runtime_error("Failed to open file: " + filePath.string());
  }

  const auto mdContext = std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_free)>(EVP_MD_CTX_new(), EVP_MD_CTX_free);
  if (!mdContext) {
    throw std::runtime_error("Failed to create MD5 context");
  }

  if (EVP_DigestInit_ex(mdContext.get(), EVP_md5(), nullptr) != 1) {
    throw std::runtime_error("Failed to initialize MD5 context");
  }

  constexpr size_t bufferSize = 4096;
  char buffer[bufferSize];
  while (file.read(buffer, bufferSize)) {
    if (const auto bytesRead = static_cast<size_t>(file.gcount()); EVP_DigestUpdate(mdContext.get(), buffer, bytesRead) != 1) {
      throw std::runtime_error("MD5 update failed");
    }
  }
  if (const auto bytesRead = static_cast<size_t>(file.gcount()); bytesRead > 0) {
    if (EVP_DigestUpdate(mdContext.get(), buffer, bytesRead) != 1) {
      throw std::runtime_error("MD5 update failed");
    }
  }

  std::array<unsigned char, EVP_MAX_MD_SIZE> digest{};
  uint32_t digestLength;
  if (EVP_DigestFinal_ex(mdContext.get(), digest.data(), &digestLength) != 1) {
    throw std::runtime_error("MD5 finalization failed");
  }

  std::ostringstream oss;
  oss << std::hex << std::setfill('0');
  for (uint32_t i = 0; i < digestLength; ++i) {
    oss << std::setw(2) << static_cast<unsigned>(digest[i]);
  }

  return oss.str();
}
}  // namespace fox
