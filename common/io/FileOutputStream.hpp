#pragma once
#include <filesystem>
#include <fstream>
#include <vector>
#include "AbstractOutputStream.hpp"

namespace common::io
{
    class FileOutputStream final : public AbstractOutputStream
    {
    public:
        FileOutputStream(const std::string& name, bool append);
        FileOutputStream(const char* name, bool append);
        FileOutputStream(const std::filesystem::path& file, bool append);
        ~FileOutputStream() override;
        void write(std::byte b) override;
        void write(const std::vector<std::byte>& buffer) override;
        void write(const std::vector<std::byte>& buffer, size_t offset, size_t len) override;
        void close() override;
        void flush() override;
    private:
        std::ofstream fileStream_;
        std::string fileName_{};
    };
}
