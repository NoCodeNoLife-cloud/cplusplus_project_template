#pragma once
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "AbstractWriter.hpp"

namespace fox
{
    /// @brief Abstract base class for filter writers.
    /// This class provides a common interface for writers that filter or transform data before writing it to an underlying
    /// output writer. Subclasses should implement the specific filtering or transformation logic.
    class AbstractFilterWriter : public AbstractWriter
    {
    public:
        /// @brief Constructs a filter writer with the specified output writer.
        /// @param outputWriter The underlying writer to which filtered data will be written.
        /// @throws std::invalid_argument if outputWriter is null.
        explicit AbstractFilterWriter(std::unique_ptr<AbstractWriter> outputWriter);

        ~AbstractFilterWriter() override;

        /// @brief Writes a single character to the output writer.
        /// This method overrides the base class method to provide filtering functionality.
        /// The character is processed and then passed to the underlying output writer.
        /// @param c The character to write.
        void write(char c) override;

        /// @brief Writes a sequence of characters from a vector to the output writer.
        /// This method overrides the base class method to provide filtering functionality.
        /// The characters are processed and then passed to the underlying output writer.
        /// @param cBuf The vector containing the characters to write.
        /// @param off The starting offset in the vector.
        /// @param len The number of characters to write.
        /// @throws std::out_of_range if off + len exceeds the buffer size.
        void write(const std::vector<char>& cBuf, size_t off, size_t len) override;

        /// @brief Writes a sequence of characters from a vector to the output writer.
        /// This method overrides the base class method to provide filtering functionality.
        /// The characters are processed and then passed to the underlying output writer.
        /// @param cBuf The vector containing the characters to write.
        void write(const std::vector<char>& cBuf) override;

        /// @brief Writes a sequence of characters from a string to the output writer.
        /// This method overrides the base class method to provide filtering functionality.
        /// The characters are processed and then passed to the underlying output writer.
        /// @param str The string containing the characters to write.
        /// @param off The starting offset in the string.
        /// @param len The number of characters to write.
        /// @throws std::out_of_range if off + len exceeds the string size.
        void write(const std::string& str, size_t off, size_t len) override;

        /// @brief Writes a sequence of characters from a string to the output writer.
        /// This method overrides the base class method to provide filtering functionality.
        /// The characters are processed and then passed to the underlying output writer.
        /// @param str The string containing the characters to write.
        void write(const std::string& str) override;

        /// @brief Flushes the output writer.
        /// This method overrides the base class method to provide filtering functionality.
        /// It ensures that any buffered data is written to the underlying output writer.
        void flush() override;

        /// @brief Closes the output writer.
        /// This method overrides the base class method to provide filtering functionality.
        /// It ensures that the underlying output writer is also closed.
        void close() override;

    protected:
        std::unique_ptr<AbstractWriter> output_writer_;

    private:
        /// @brief Checks if the output stream is available.
        /// @throws std::runtime_error if the output stream is not available.
        void checkOutputStream() const;
    };

    inline AbstractFilterWriter::AbstractFilterWriter(std::unique_ptr<AbstractWriter> outputWriter)
        : output_writer_(std::move(outputWriter))
    {
        if (!output_writer_)
        {
            throw std::invalid_argument("Output writer cannot be null");
        }
    }

    inline AbstractFilterWriter::~AbstractFilterWriter() = default;

    inline void AbstractFilterWriter::write(const char c)
    {
        checkOutputStream();
        output_writer_->write(c);
    }

    inline void AbstractFilterWriter::write(const std::vector<char>& cBuf, const size_t off, const size_t len)
    {
        checkOutputStream();
        if (off + len > cBuf.size())
        {
            throw std::out_of_range("Buffer overflow");
        }
        output_writer_->write(cBuf, off, len);
    }

    inline void AbstractFilterWriter::write(const std::vector<char>& cBuf)
    {
        checkOutputStream();
        output_writer_->write(cBuf);
    }

    inline void AbstractFilterWriter::write(const std::string& str, const size_t off, const size_t len)
    {
        checkOutputStream();
        if (off + len > str.size())
        {
            throw std::out_of_range("String overflow");
        }
        output_writer_->write(str, off, len);
    }

    inline void AbstractFilterWriter::write(const std::string& str)
    {
        checkOutputStream();
        output_writer_->write(str);
    }

    inline void AbstractFilterWriter::flush()
    {
        checkOutputStream();
        output_writer_->flush();
    }

    inline void AbstractFilterWriter::close()
    {
        checkOutputStream();
        flush();
        output_writer_->close();
    }

    inline void AbstractFilterWriter::checkOutputStream() const
    {
        if (!output_writer_)
        {
            throw std::runtime_error("Output stream is not available");
        }
    }
}
