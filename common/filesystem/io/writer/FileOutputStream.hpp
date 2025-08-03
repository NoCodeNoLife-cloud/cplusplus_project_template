#pragma once
#include <filesystem>
#include <fstream>
#include <vector>

#include "AbstractOutputStream.hpp"

namespace common {
class FileOutputStream final : public AbstractOutputStream {
 public:
  FileOutputStream(const std::string& name, bool append);
  FileOutputStream(const char* name, bool append);
  FileOutputStream(const std::filesystem::path& file, bool append);
  ~FileOutputStream() override;

  /// @brief Writes a single byte to the file stream.
  /// @param b The byte to write.
  void write(std::byte b) override;

  /// @brief Writes a vector of bytes to the file stream.
  /// @param buffer The vector of bytes to write.
  void write(const std::vector<std::byte>& buffer) override;

  /// @brief Writes a portion of a vector of bytes to the file stream.
  /// @param buffer The vector of bytes to write from.
  /// @param offset The starting position in the buffer.
  /// @param len The number of bytes to write.
  void write(const std::vector<std::byte>& buffer, size_t offset, size_t len) override;

  /// @brief Closes the file stream.
  void close() override;

  /// @brief Flushes the file stream.
  void flush() override;

 private:
  std::ofstream file_stream_;
  std::string file_name_{};
};
}  // namespace common
