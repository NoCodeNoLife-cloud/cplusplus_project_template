#include "PipedReader.hpp"
#include <utility>

namespace framework::io {
    PipedReader::PipedReader() : PipedReader(DEFAULT_PIPE_SIZE) {}

    PipedReader::PipedReader(const int32_t pipeSize) : buffer_(pipeSize), buffer_size_(pipeSize) {}

    PipedReader::PipedReader(const std::shared_ptr<PipedWriter>& src) : PipedReader(src, DEFAULT_PIPE_SIZE) {}

    PipedReader::PipedReader(std::shared_ptr<PipedWriter> src, const int32_t pipeSize) : src_(std::move(src)), buffer_(pipeSize), buffer_size_(pipeSize) {}

    PipedReader::~PipedReader() { close(); }

    auto PipedReader::close() -> void {
        src_.reset();
        buffer_.clear();
        read_pos_ = write_pos_ = 0;
    }

    int32_t PipedReader::read() {
        std::lock_guard lock(read_mutex_);
        if (!ready()) { return -1; }
        return buffer_[read_pos_++ % buffer_size_];
    }

    auto PipedReader::read(std::vector<char>& cBuf, const size_t off, const size_t len) -> size_t {
        std::lock_guard lock(read_mutex_);
        if (off + len > cBuf.size()) { throw std::out_of_range("index out of range"); }
        size_t bytesRead = 0;
        while (bytesRead < len && ready())
        {
            cBuf[off + bytesRead] = buffer_[read_pos_++ % buffer_size_];
            ++bytesRead;
        }
        return bytesRead;
    }

    bool PipedReader::ready() const { return read_pos_ != write_pos_; }

    auto PipedReader::connect(std::shared_ptr<PipedWriter> src) -> void {
        if (src_) { throw std::runtime_error("already connected"); }
        src_ = std::move(src);
    }

    auto PipedReader::mark(size_t readAheadLimit) -> void {
        // no-op
    }

    auto PipedReader::reset() -> void {
        // no-op
    }

    bool PipedReader::markSupported() const { return false; }

    auto PipedReader::writeToBuffer(const char c) -> void {
        if (buffer_size_ == 0) { throw std::runtime_error("Buffer not initialized or closed."); }
        const size_t nextWritePos = (write_pos_ + 1) % buffer_size_;
        if (nextWritePos == read_pos_) { throw std::runtime_error("Pipe buffer overflow: Reader has not consumed data."); }
        buffer_[write_pos_] = c;
        write_pos_ = nextWritePos;
    }
} // namespace framework::io
