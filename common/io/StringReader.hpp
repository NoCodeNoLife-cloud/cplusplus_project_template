#pragma once
#include <ostream>
#include <string>
#include <utility>
#include "AbstractReader.hpp"

namespace common::io
{
    class StringReader final : public AbstractReader
    {
    public:
        explicit StringReader(std::string s);
        ~StringReader() override;
        auto close() -> void override;
        auto mark(size_t readAheadLimit) -> void override;
        [[nodiscard]] auto markSupported() const -> bool override;
        auto read() -> int override;
        auto read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t override;
        [[nodiscard]] auto ready() const -> bool override;
        auto reset() -> void override;
        auto skip(size_t ns) -> size_t override;
    private:
        std::string source_;
        size_t position_;
        size_t markPosition_;
        bool markSet_;
    };

    inline StringReader::StringReader(std::string s): source_(std::move(s)), position_(0), markPosition_(0), markSet_(false) {}

    inline StringReader::~StringReader() = default;

    inline auto StringReader::close() -> void
    {
        source_.clear();
        position_ = 0;
        markPosition_ = 0;
        markSet_ = false;
    }

    inline auto StringReader::mark(const size_t readAheadLimit) -> void
    {
        markPosition_ = readAheadLimit;
        markSet_ = true;
    }

    inline bool StringReader::markSupported() const
    {
        return true;
    }

    inline int StringReader::read()
    {
        if (position_ >= source_.size())
        {
            return -1; // EOF
        }
        return source_[position_++];
    }

    inline auto StringReader::read(std::vector<char>& cBuf, const size_t off, const size_t len) -> size_t
    {
        if (off >= cBuf.size())
        {
            throw std::invalid_argument("Offset is out of bounds of the buffer");
        }
        const size_t maxRead = std::min(len, source_.size() - position_);
        const size_t actualRead = std::min(maxRead, cBuf.size() - off);
        for (size_t i = 0; i < actualRead; ++i)
        {
            if (position_ < source_.size())
            {
                cBuf[off + i] = source_[position_++];
            }
            else
            {
                break;
            }
        }
        return actualRead;
    }

    inline bool StringReader::ready() const
    {
        return position_ < source_.size();
    }

    inline auto StringReader::reset() -> void
    {
        if (!markSet_)
        {
            position_ = 0;
        }
        else
        {
            position_ = markPosition_;
        }
    }

    inline size_t StringReader::skip(const size_t ns)
    {
        const size_t charsToSkip = std::min(ns, source_.size() - position_);
        position_ += charsToSkip;
        return static_cast<long>(charsToSkip);
    }
}
