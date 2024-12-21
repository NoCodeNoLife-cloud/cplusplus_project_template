#pragma once
#include <memory>
#include <stdexcept>
#include "AbstractWriter.hpp"

namespace common::io {
/// \brief Abstract class for writing filtered character streams.
/// \details The FilterWriter class is an abstract class for writing filtered character streams.
/// It provides methods to write characters, strings, and character arrays to a stream.
/// The class is designed for subclassing by users who want to write filtered character streams.
class AbstractFilterWriter abstract : public AbstractWriter {
public:
  explicit AbstractFilterWriter(std::unique_ptr<AbstractWriter> outputWriter) : outputWriter_(std::move(outputWriter)) {
    if (!outputWriter_) {
      throw std::invalid_argument("Output writer cannot be null");
    }
  }

  ~AbstractFilterWriter() override = default;

  /// \brief Writes a single character to the output stream.
  /// \param c The character to be written.
  /// \throws std::runtime_error if the output stream is not available.
  auto write(const char c) -> void override {
    if (!outputWriter_) {
      throw std::runtime_error("Output stream is not available");
    }
    outputWriter_->write(c);
  }

  /// \brief Writes a portion of a character buffer to the output stream.
  /// \param cBuf The buffer containing characters to write.
  /// \param off The offset in the buffer from which to start writing.
  /// \param len The number of characters to write.
  /// \throws std::runtime_error if the output stream is not available.
  /// \throws std::out_of_range if the buffer overflows.
  auto write(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void override {
    if (!outputWriter_) {
      throw std::runtime_error("Output stream is not available");
    }
    if (off + len > cBuf.size()) {
      throw std::out_of_range("Buffer overflow");
    }
    outputWriter_->write(cBuf, off, len);
  }

  /// \brief Writes a character buffer to the output stream.
  /// \param cBuf The buffer containing characters to write.
  /// \throws std::runtime_error if the output stream is not available.
  auto write(const std::vector<char>& cBuf) -> void override {
    if (!outputWriter_) {
      throw std::runtime_error("Output stream is not available");
    }
    outputWriter_->write(cBuf);
  }

  /// \brief Writes a portion of a string to the output stream.
  /// \param str The string containing characters to write.
  /// \param off The offset in the string from which to start writing.
  /// \param len The number of characters to write.
  /// \throws std::runtime_error if the output stream is not available.
  /// \throws std::out_of_range if the string overflows.
  auto write(const std::string& str, const size_t off, const size_t len) -> void override {
    if (!outputWriter_) {
      throw std::runtime_error("Output stream is not available");
    }
    if (off + len > str.size()) {
      throw std::out_of_range("String overflow");
    }
    outputWriter_->write(str, off, len);
  }

  /// \brief Writes a string to the output stream.
  /// \param str The string containing characters to write.
  /// \throws std::runtime_error if the output stream is not available.
  auto write(const std::string& str) -> void override {
    if (!outputWriter_) {
      throw std::runtime_error("Output stream is not available");
    }
    outputWriter_->write(str);
  }

  /// \brief Flushes the output stream.
  /// \throws std::runtime_error if the output stream is not available.
  auto flush() -> void override {
    if (!outputWriter_) {
      throw std::runtime_error("Output stream is not available");
    }
    outputWriter_->flush();
  }

  /// \brief Closes the output stream.
  /// \throws std::runtime_error if the output stream is not available.
  auto close() -> void override {
    if (!outputWriter_) {
      throw std::runtime_error("Output stream is not available");
    }
    flush();
    outputWriter_->close();
  }

protected:
  std::unique_ptr<AbstractWriter> outputWriter_;
};
}
