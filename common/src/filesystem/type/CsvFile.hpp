#pragma once
#include <rapidcsv.h>

#include <string>
#include <vector>

namespace common
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
}
