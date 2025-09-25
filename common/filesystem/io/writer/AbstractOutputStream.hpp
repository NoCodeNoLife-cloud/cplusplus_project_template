#pragma once
#include <format>
#include <stdexcept>
#include <vector>

#include "filesystem/io/interface/ICloseable.hpp"
#include "filesystem/io/interface/IFlushable.hpp"

namespace fox
{
    /// @brief Abstract base class for all output stream implementations.
    /// @details This class provides the basic contract for writing data to an output stream.
    /// It defines pure virtual methods that must be implemented by concrete subclasses.
    /// The class also implements the ICloseable and IFlushable interfaces to provide
    /// standard close and flush functionality.
    class AbstractOutputStream : public ICloseable, public IFlushable
    {
    public:
        ~AbstractOutputStream() override = default;

        /// @brief Writes a single byte to the output stream.
        /// @param b The byte to be written.
        virtual void write(std::byte b) = 0;

        /// @brief Writes all bytes from the specified buffer to the output stream.
        /// @param buffer The buffer containing bytes to be written.
        virtual auto write(const std::vector<std::byte>& buffer) -> void;

        /// @brief Writes a specified number of bytes from the buffer starting at the given offset to the output stream.
        /// @param buffer The buffer containing bytes to be written.
        /// @param offset The start offset in the buffer.
        /// @param len The number of bytes to write.
        /// @throws std::out_of_range if offset + len exceeds buffer size.
        virtual auto write(const std::vector<std::byte>& buffer, size_t offset, size_t len) -> void;

        /// @brief Writes a specified number of bytes from the buffer to the output stream.
        /// @param buffer The buffer containing bytes to be written.
        /// @param length The number of bytes to write.
        virtual auto write(const std::byte* buffer, size_t length) -> void = 0;
    };

    inline auto AbstractOutputStream::write(const std::vector<std::byte>& buffer) -> void
    {
        if (!buffer.empty())
        {
            write(buffer, 0, buffer.size());
        }
    }

    inline auto AbstractOutputStream::write(const std::vector<std::byte>& buffer, const size_t offset, const size_t len) -> void
    {
        if (offset + len > buffer.size())
        {
            throw std::out_of_range("Buffer offset/length out of range");
        }

        for (size_t i = 0; i < len; ++i)
        {
            write(buffer[offset + i]);
        }
    }
}
