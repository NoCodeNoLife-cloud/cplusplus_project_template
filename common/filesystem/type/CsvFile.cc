#include "CsvFile.hpp"

namespace common {
CsvFile::CsvFile(const std::string& file_path) : file_path_(file_path) {
  try {
    csv_doc_ = rapidcsv::Document(file_path);
    is_valid_ = true;
  } catch (const std::exception& e) {
    std::cerr << "Error loading CSV file: " << e.what() << std::endl;
    is_valid_ = false;
  }
}

auto CsvFile::getRowCount() const -> uint64_t {
  if (!is_valid_) return 0;
  return csv_doc_.GetRowCount();
}

auto CsvFile::getColumnCount() const -> uint64_t {
  if (!is_valid_) return 0;
  return csv_doc_.GetColumnCount();
}

auto CsvFile::insertRow(const uint64_t insertIndex, const std::vector<std::string>& item) -> bool {
  if (!is_valid_) return false;
  if (insertIndex > getRowCount()) {
    std::cerr << "Invalid insert index: " << insertIndex << std::endl;
    return false;
  }
  if (getColumnCount() != 0 && item.size() != getColumnCount()) {
    std::cerr << "Column count mismatch. Expected: " << getColumnCount() << ", Got: " << item.size() << std::endl;
    return false;
  }
  try {
    csv_doc_.InsertRow(insertIndex, item);
    return true;
  } catch (const std::exception& e) {
    std::cerr << "Insert row failed: " << e.what() << std::endl;
    return false;
  }
}

auto CsvFile::pushBack(const std::vector<std::string>& item) -> bool { return insertRow(getRowCount(), item); }

auto CsvFile::save(const std::string& path) -> bool {
  if (!is_valid_) return false;
  try {
    if (path.empty()) {
      csv_doc_.Save();
    } else {
      csv_doc_.Save(path);
    }
    return true;
  } catch (const std::exception& e) {
    std::cerr << "Failed to save file: " << e.what() << std::endl;
    return false;
  }
}
}  // namespace common
