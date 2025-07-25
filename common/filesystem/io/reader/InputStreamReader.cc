#include "InputStreamReader.hpp"

namespace common
{
    InputStreamReader::InputStreamReader(std::shared_ptr<AbstractReader> input) : reader_(std::move(input))
    {
        if (!reader_)
        {
            throw std::invalid_argument("Input stream cannot be null");
        }
    }

    InputStreamReader::InputStreamReader(std::shared_ptr<AbstractReader> input, const std::string& charsetName) :
        reader_(std::move(input))
    {
        if (!reader_)
        {
            throw std::invalid_argument("Input stream cannot be null");
        }
        if (charsetName != "UTF-8")
        {
            throw std::invalid_argument("Only UTF-8 charset is supported in this implementation");
        }
    }

    InputStreamReader::~InputStreamReader() = default;

    int32_t InputStreamReader::read()
    {
        if (!reader_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        std::vector<char> byteBuffer(4, 0);
        if (const size_t bytesRead = reader_->read(byteBuffer, 0, 1); bytesRead == 0)
        {
            return -1;
        }
        try
        {
            const char32_t charValue = converter_.from_bytes(byteBuffer.data())[0];
            return static_cast<int32_t>(charValue);
        }
        catch (const std::exception&)
        {
            throw std::runtime_error("Failed to decode byte to character");
        }
    }

    auto InputStreamReader::read(std::vector<char>& cBuf, const size_t off, const size_t len) -> size_t
    {
        if (!reader_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        if (off + len > cBuf.size())
        {
            throw std::out_of_range("Buffer overflow");
        }
        std::vector<char> byteBuffer(len, 0);
        const size_t bytesRead = reader_->read(byteBuffer, 0, len);
        if (bytesRead == 0)
        {
            return -1;
        }
        try
        {
            auto chars = converter_.from_bytes(byteBuffer.data(), byteBuffer.data() + bytesRead);
            const size_t charsToCopy = std::min(chars.size(), len);
            std::copy_n(chars.begin(), charsToCopy, cBuf.begin() + static_cast<std::vector<char>::difference_type>(off));
            return charsToCopy;
        }
        catch (const std::exception&)
        {
            throw std::runtime_error("Failed to decode bytes to characters");
        }
    }

    bool InputStreamReader::ready() const
    {
        if (!reader_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        return reader_->ready();
    }

    auto InputStreamReader::close() -> void
    {
        if (!reader_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        reader_->close();
    }

    auto InputStreamReader::mark(size_t) -> void
    {
        throw std::runtime_error("Mark not supported");
    }

    auto InputStreamReader::reset() -> void
    {
        throw std::runtime_error("Reset not supported");
    }
}
