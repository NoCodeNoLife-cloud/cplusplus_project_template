#pragma once
#include <rapidcsv.h>
#include <string>

namespace common
{
    class CsvFile
    {
    public:
        explicit CsvFile(const std::string& file_path);
        [[nodiscard]] auto getRowCount() const -> uint64_t;
        [[nodiscard]] auto getColumnCount() const -> uint64_t;
        auto insertRow(uint64_t insertIndex, const std::vector<std::string>& item) -> bool;
        auto pushBack(const std::vector<std::string>& item) -> bool;
        auto save(const std::string& path = "") -> bool;

    private:
        std::string file_path_{};
        rapidcsv::Document csv_doc_{};
        bool is_valid_{false};
    };
}
