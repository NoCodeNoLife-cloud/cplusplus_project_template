#include "FileInputStream.hpp"

namespace fox {
FileInputStream::FileInputStream(const std::string& name) {
  if (!std::filesystem::exists(name)) {
    throw std::ios_base::failure("FileNotFoundException: File does not exist.");
  }
  if (std::filesystem::is_directory(name)) {
    throw std::ios_base::failure("FileNotFoundException: Path is a directory.");
  }
  file_stream_.open(name, std::ios::binary);
  if (!file_stream_.is_open()) {
    throw std::ios_base::failure("FileNotFoundException: Unable to open file.");
  }
  file_name_ = name;
}

FileInputStream::FileInputStream(const char* name) : FileInputStream(std::string(name)) {}

FileInputStream::FileInputStream(const std::filesystem::path& file) : FileInputStream(file.string()) {}

FileInputStream::~FileInputStream() { close(); }

auto FileInputStream::read() -> std::byte {
  std::byte byte;
  if (file_stream_.read(reinterpret_cast<char*>(&byte), 1)) {
    return byte;
  }
  return static_cast<std::byte>(-1);
}

size_t FileInputStream::read(std::vector<std::byte>& buffer) { return read(buffer, 0, buffer.size()); }

size_t FileInputStream::read(std::vector<std::byte>& buffer, const size_t offset, const size_t len) {
  if (offset + len > buffer.size()) {
    throw std::invalid_argument("Invalid buffer, offset, or length.");
  }
  file_stream_.read(reinterpret_cast<char*>(buffer.data() + offset), static_cast<std::streamsize>(len));
  return file_stream_.gcount();
}

size_t FileInputStream::skip(const size_t n) {
  file_stream_.seekg(static_cast<std::streamoff>(n), std::ios::cur);
  return file_stream_.good() ? static_cast<std::streamoff>(n) : 0;
}

auto FileInputStream::available() -> size_t {
  const auto current = file_stream_.tellg();
  file_stream_.seekg(0, std::ios::end);
  const auto end = file_stream_.tellg();
  file_stream_.seekg(current, std::ios::beg);
  return end - current;
}

auto FileInputStream::close() -> void {
  if (file_stream_.is_open()) {
    file_stream_.close();
  }
}

bool FileInputStream::markSupported() const { return false; }
}  // namespace fox
