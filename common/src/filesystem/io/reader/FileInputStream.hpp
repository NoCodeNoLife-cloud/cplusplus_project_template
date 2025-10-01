#pragma once
#include <filesystem>
#include <fstream>
#include <vector>

#include "AbstractInputStream.hpp"

namespace fox
{
    /// @brief A FileInputStream class for reading data from a file.
    /// @details This class provides functionality to read bytes from a file,
    ///          including methods for reading single bytes, multiple bytes,
    ///          skipping bytes, checking available bytes, and closing the stream.
    class FileInputStream final : public AbstractInputStream
    {
    public:
        explicit FileInputStream(const std::string& name);
        explicit FileInputStream(const char* name);
        explicit FileInputStream(const std::filesystem::path& file);
        ~FileInputStream() override;

        /// @brief Read a single byte from the stream.
        /// @return The byte read or EOF (-1) if the end of the stream is reached.
        auto read() -> std::byte override;

        /// @brief Read bytes from the stream.
        /// @param buffer The buffer to read into.
        /// @return The number of bytes read.
        auto read(std::vector<std::byte>& buffer) -> size_t override;

        /// @brief Read bytes from the stream.
        /// @param buffer The buffer to read into.
        /// @param offset The offset to start reading from.
        /// @param len The number of bytes to read.
        /// @return The number of bytes read.
        auto read(std::vector<std::byte>& buffer, size_t offset, size_t len) -> size_t override;

        /// @brief Skip bytes in the stream.
        /// @param n The number of bytes to skip.
        /// @return The number of bytes skipped.
        auto skip(size_t n) -> size_t override;

        /// @brief Get the number of bytes available to read.
        /// @return The number of bytes available to read.
        auto available() -> size_t override;

        /// @brief Close the stream.
        auto close() -> void override;

        /// @brief Checks if this input stream has been closed.
        /// @return true if this input stream has been closed, false otherwise.
        [[nodiscard]] auto isClosed() const -> bool override;

        /// @brief Check if the stream supports marking.
        /// @return True if the stream supports marking, false otherwise.
        [[nodiscard]] auto markSupported() const -> bool override;

    private:
        std::ifstream file_stream_;
        std::string file_name_{};
        bool closed_{false};
    };
}
