#pragma once
#include <fstream>
#include <vector>
#include <glog/logging.h>

#include "AbstractWriter.hpp"


namespace common
{
    class BufferedWriter final : public AbstractWriter, public IAppendable<BufferedWriter>
    {
    public:
        explicit BufferedWriter(std::unique_ptr<std::ofstream> os, size_t size = DEFAULT_BUFFER_SIZE);
        ~BufferedWriter() override;
        auto write(const std::string& str) -> void override;
        auto write(const std::vector<char>& cBuf, size_t off, size_t len) -> void override;
        auto newLine() -> BufferedWriter&;
        auto flush() -> void override;
        auto close() -> void override;
        auto append(char c) -> BufferedWriter& override;
        auto append(const std::string& str) -> BufferedWriter& override;
        auto append(const std::string& str, size_t start, size_t end) -> BufferedWriter& override;
        [[nodiscard]] auto toString() const -> std::string override;

    private:
        static constexpr size_t DEFAULT_BUFFER_SIZE = 1024;
        std::unique_ptr<std::ofstream> output_stream_;
        std::vector<char> buffer_;
        size_t buffer_size_;
    };
}
