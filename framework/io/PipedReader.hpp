#pragma once
#include <mutex>
#include "AbstractReader.hpp"
#include "PipedWriter.hpp"

namespace framework::io {
    class PipedWriter;

    class PipedReader final : public AbstractReader
    {
    public:
        PipedReader();

        explicit PipedReader(int32_t pipeSize);

        explicit PipedReader(const std::shared_ptr<PipedWriter>& src);

        PipedReader(std::shared_ptr<PipedWriter> src, int32_t pipeSize);

        ~PipedReader() override;

        auto close() -> void override;

        auto read() -> int32_t override;

        auto read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t override;

        [[nodiscard]] auto ready() const -> bool override;

        auto connect(std::shared_ptr<PipedWriter> src) -> void;

        auto mark(size_t readAheadLimit) -> void override;

        auto reset() -> void override;

        [[nodiscard]] auto markSupported() const -> bool override;

        auto writeToBuffer(char c) -> void;

    private:
        static constexpr int32_t DEFAULT_PIPE_SIZE = 1024;
        std::shared_ptr<PipedWriter> src_;
        std::vector<char> buffer_;
        size_t buffer_size_{0};
        size_t read_pos_{0};
        size_t write_pos_{0};
        std::mutex read_mutex_;
    };
} // namespace framework::io
