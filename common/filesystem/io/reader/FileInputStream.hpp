#pragma once
#include <filesystem>
#include <fstream>
#include <vector>

#include "AbstractInputStream.hpp"

namespace common {
class FileInputStream final : public AbstractInputStream {
 public:
  explicit FileInputStream(const std::string& name);
  explicit FileInputStream(const char* name);
  explicit FileInputStream(const std::filesystem::path& file);
  ~FileInputStream() override;
  auto read() -> std::byte override;
  auto read(std::vector<std::byte>& buffer) -> size_t override;
  auto read(std::vector<std::byte>& buffer, size_t offset, size_t len) -> size_t override;
  auto skip(size_t n) -> size_t override;
  auto available() -> size_t override;
  auto close() -> void override;
  [[nodiscard]] auto markSupported() const -> bool override;

 private:
  std::ifstream file_stream_;
  std::string file_name_{};
};
}  // namespace common
