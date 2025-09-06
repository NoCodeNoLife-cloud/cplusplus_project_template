#include "FileOutputStream.hpp"

namespace fox {
FileOutputStream::FileOutputStream(const std::string& name, const bool append) {
  if (std::filesystem::exists(name) && std::filesystem::is_directory(name)) {
    throw std::ios_base::failure("FileNotFoundException: Path is a directory.");
  }
  file_stream_.open(name, std::ios::binary | (append ? std::ios::app : std::ios::trunc));
  if (!file_stream_.is_open()) {
    throw std::ios_base::failure("FileNotFoundException: Unable to open or create file.");
  }
  file_name_ = name;
}

FileOutputStream::FileOutputStream(const char* name, const bool append) : FileOutputStream(std::string(name), append) {}

FileOutputStream::FileOutputStream(const std::filesystem::path& file, const bool append) : FileOutputStream(file.string(), append) {}

FileOutputStream::~FileOutputStream() { close(); }

void FileOutputStream::write(std::byte b) {
  if (!file_stream_) {
    throw std::ios_base::failure("IOException: Stream is not writable.");
  }
  const char byte = static_cast<char>(b);
  file_stream_.write(&byte, 1);
}

void FileOutputStream::write(const std::vector<std::byte>& buffer) { write(buffer, 0, buffer.size()); }

void FileOutputStream::write(const std::vector<std::byte>& buffer, const size_t offset, const size_t len) {
  if (offset > buffer.size() || len > buffer.size() - offset) {
    throw std::invalid_argument("Invalid buffer, offset, or length.");
  }
  if (!file_stream_) {
    throw std::ios_base::failure("IOException: Stream is not writable.");
  }
  file_stream_.write(reinterpret_cast<const char*>(buffer.data() + offset), static_cast<std::streamsize>(len));
}

void FileOutputStream::close() {
  if (file_stream_.is_open()) {
    file_stream_.close();
  }
}

void FileOutputStream::flush() {
  if (!file_stream_) {
    throw std::ios_base::failure("IOException: Stream is not writable.");
  }
  file_stream_.flush();
}
}  // namespace fox
