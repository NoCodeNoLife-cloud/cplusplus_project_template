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
        explicit StringReader(std::string s) : source_(std::move(s)), position_(0), markPosition_(0), markSet_(false)
        {
        }

        ~StringReader() override = default;

        auto close() -> void override
        {
            source_.clear();
            position_ = 0;
            markPosition_ = 0;
            markSet_ = false;
        }

        auto mark(const size_t readAheadLimit) -> void override
        {
            markPosition_ = readAheadLimit;
            markSet_ = true;
        }

        [[nodiscard]] auto markSupported() const -> bool override
        {
            return true;
        }

        auto read() -> int override
        {
            if (position_ >= source_.size())
            {
                return -1; // EOF
            }
            return source_[position_++];
        }

        auto read(std::vector<char>& cBuf, const size_t off, const size_t len) -> size_t override
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

        [[nodiscard]] auto ready() const -> bool override
        {
            return position_ < source_.size();
        }

        auto reset() -> void override
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

        auto skip(const size_t ns) -> size_t override
        {
            const size_t charsToSkip = std::min(ns, source_.size() - position_);
            position_ += charsToSkip;
            return static_cast<long>(charsToSkip);
        }

    private:
        std::string source_;
        size_t position_;
        size_t markPosition_;
        bool markSet_;
    };
}
