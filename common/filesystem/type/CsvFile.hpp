#pragma once
#include <rapidcsv.h>

#include <exception>
#include <iostream>
#include <string>
#include <vector>

namespace fox
{
    /// @brief A class to handle CSV file operations using rapidcsv library
    /// @details This class provides functionalities to read, modify and save CSV files.
    /// It encapsulates the rapidcsv::Document object and provides a simplified interface
    /// for common CSV operations.
    class CsvFile
    {
    public:
        /// @brief Constructs a CsvFile object from a file path
        /// @param file_path The path to the CSV file to load
        explicit CsvFile(const std::string& file_path) noexcept;

        /// @brief Get the number of rows in the CSV file
        /// @return The number of rows as uint64_t
        [[nodiscard]] auto getRowCount() const noexcept -> uint64_t;

        /// @brief Get the number of columns in the CSV file
        /// @return The number of columns as uint64_t
        [[nodiscard]] auto getColumnCount() const noexcept -> uint64_t;

        /// @brief Insert a row at the specified index
        /// @param insertIndex The index where the row should be inserted
        /// @param item The vector of strings representing the row data
        /// @return True if successful, false otherwise
        auto insertRow(uint64_t insertIndex, const std::vector<std::string>& item) noexcept -> bool;

        /// @brief Add a row to the end of the CSV file
        /// @param item The vector of strings representing the row data
        /// @return True if successful, false otherwise
        auto pushBack(const std::vector<std::string>& item) noexcept -> bool;

        /// @brief Save the CSV file to disk
        /// @param path The path where to save the file (uses original path if empty)
        /// @return True if successful, false otherwise
        auto save(const std::string& path = {}) noexcept -> bool;

    private:
        std::string file_path_{};
        rapidcsv::Document csv_doc_{};
        bool is_valid_{false};
    };

    inline CsvFile::CsvFile(const std::string& file_path) noexcept : file_path_(file_path)
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

    inline auto CsvFile::getRowCount() const noexcept -> uint64_t
    {
        if (!is_valid_)
            return 0;
        return csv_doc_.GetRowCount();
    }

    inline auto CsvFile::getColumnCount() const noexcept -> uint64_t
    {
        if (!is_valid_)
            return 0;
        return csv_doc_.GetColumnCount();
    }

    inline auto CsvFile::insertRow(const uint64_t insertIndex, const std::vector<std::string>& item) noexcept -> bool
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

    inline auto CsvFile::pushBack(const std::vector<std::string>& item) noexcept -> bool
    {
        return insertRow(getRowCount(), item);
    }

    inline auto CsvFile::save(const std::string& path) noexcept -> bool
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
}
