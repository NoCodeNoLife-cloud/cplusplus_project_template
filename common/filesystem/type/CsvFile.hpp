#pragma once
#include <rapidcsv.h>

#include <exception>
#include <iostream>
#include <string>

namespace fox
{
    /// @brief A class to handle CSV file operations using rapidcsv library
    /// @details This class provides functionalities to read, modify and save CSV files.
    /// It encapsulates the rapidcsv::Document object and provides a simplified interface
    /// for common CSV operations.
    class CsvFile
    {
    public:
        explicit CsvFile(const std::string& file_path) : file_path_(file_path)
        {
            try
            {
                csv_doc_ = rapidcsv::Document(file_path);
                is_valid_ = true;
            }
            catch (const std::exception& e)
            {
                std::cerr << "Error loading CSV file: " << e.what() << std::endl;
                is_valid_ = false;
            }
        }

        /// @brief Get the number of rows in the CSV file
        /// @return The number of rows as uint64_t
        [[nodiscard]] auto getRowCount() const -> uint64_t
        {
            if (!is_valid_)
                return 0;
            return csv_doc_.GetRowCount();
        }

        /// @brief Get the number of columns in the CSV file
        /// @return The number of columns as uint64_t
        [[nodiscard]] auto getColumnCount() const -> uint64_t
        {
            if (!is_valid_)
                return 0;
            return csv_doc_.GetColumnCount();
        }

        /// @brief Insert a row at the specified index
        /// @param insertIndex The index where the row should be inserted
        /// @param item The vector of strings representing the row data
        /// @return True if successful, false otherwise
        auto insertRow(const uint64_t insertIndex, const std::vector<std::string>& item) -> bool
        {
            if (!is_valid_)
                return false;
            if (insertIndex > getRowCount())
            {
                std::cerr << "Invalid insert index: " << insertIndex << std::endl;
                return false;
            }
            if (getColumnCount() != 0 && item.size() != getColumnCount())
            {
                std::cerr << "Column count mismatch. Expected: " << getColumnCount() << ", Got: " << item.size()
                    << std::endl;
                return false;
            }
            try
            {
                csv_doc_.InsertRow(insertIndex, item);
                return true;
            }
            catch (const std::exception& e)
            {
                std::cerr << "Insert row failed: " << e.what() << std::endl;
                return false;
            }
        }

        /// @brief Add a row to the end of the CSV file
        /// @param item The vector of strings representing the row data
        /// @return True if successful, false otherwise
        auto pushBack(const std::vector<std::string>& item) -> bool
        {
            return insertRow(getRowCount(), item);
        }

        /// @brief Save the CSV file to disk
        /// @param path The path where to save the file (uses original path if empty)
        /// @return True if successful, false otherwise
        auto save(const std::string& path = "") -> bool
        {
            if (!is_valid_)
                return false;
            try
            {
                if (path.empty())
                {
                    csv_doc_.Save();
                }
                else
                {
                    csv_doc_.Save(path);
                }
                return true;
            }
            catch (const std::exception& e)
            {
                std::cerr << "Failed to save file: " << e.what() << std::endl;
                return false;
            }
        }

    private:
        std::string file_path_{};
        rapidcsv::Document csv_doc_{};
        bool is_valid_{false};
    };
} // namespace fox
