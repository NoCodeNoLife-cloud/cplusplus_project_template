#pragma once
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "AbstractWriter.hpp"

namespace fox {
/// @brief Abstract base class for filter writers.
/// This class provides a common interface for writers that filter or transform data before writing it to an underlying output writer.
/// Subclasses should implement the specific filtering or transformation logic.
class AbstractFilterWriter : public AbstractWriter {
 public:
  explicit AbstractFilterWriter(std::unique_ptr<AbstractWriter> outputWriter) : output_writer_(std::move(outputWriter)) {
    if (!output_writer_) {
      throw std::invalid_argument("Output writer cannot be null");
    }
  }

  ~AbstractFilterWriter() override = default;

  /// @brief Writes a single character to the output writer.
  /// This method overrides the base class method to provide filtering functionality.
  /// The character is processed and then passed to the underlying output writer.
  /// @param c The character to write.
  auto write(char c) -> void override {
    if (!output_writer_) {
      throw std::runtime_error("Output stream is not available");
    }
    output_writer_->write(c);
  }

  /// @brief Writes a sequence of characters from a vector to the output writer.
  /// This method overrides the base class method to provide filtering functionality.
  /// The characters are processed and then passed to the underlying output writer.
  /// @param cBuf The vector containing the characters to write.
  /// @param off The starting offset in the vector.
  /// @param len The number of characters to write.
  auto write(const std::vector<char>& cBuf, size_t off, size_t len) -> void override {
    if (!output_writer_) {
      throw std::runtime_error("Output stream is not available");
    }
    if (off + len > cBuf.size()) {
      throw std::out_of_range("Buffer overflow");
    }
    output_writer_->write(cBuf, off, len);
  }

  /// @brief Writes a sequence of characters from a vector to the output writer.
  /// This method overrides the base class method to provide filtering functionality.
  /// The characters are processed and then passed to the underlying output writer.
  /// @param cBuf The vector containing the characters to write.
  auto write(const std::vector<char>& cBuf) -> void override {
    if (!output_writer_) {
      throw std::runtime_error("Output stream is not available");
    }
    output_writer_->write(cBuf);
  }

  /// @brief Writes a sequence of characters from a string to the output writer.
  /// This method overrides the base class method to provide filtering functionality.
  /// The characters are processed and then passed to the underlying output writer.
  /// @param str The string containing the characters to write.
  /// @param off The starting offset in the string.
  /// @param len The number of characters to write.
  auto write(const std::string& str, size_t off, size_t len) -> void override {
    if (!output_writer_) {
      throw std::runtime_error("Output stream is not available");
    }
    if (off + len > str.size()) {
      throw std::out_of_range("String overflow");
    }
    output_writer_->write(str, off, len);
  }

  /// @brief Writes a sequence of characters from a string to the output writer.
  /// This method overrides the base class method to provide filtering functionality.
  /// The characters are processed and then passed to the underlying output writer.
  /// @param str The string containing the characters to write.
  auto write(const std::string& str) -> void override {
    if (!output_writer_) {
      throw std::runtime_error("Output stream is not available");
    }
    output_writer_->write(str);
  }

  /// @brief Flushes the output writer.
  /// This method overrides the base class method to provide filtering functionality.
  /// It ensures that any buffered data is written to the underlying output writer.
  auto flush() -> void override {
    if (!output_writer_) {
      throw std::runtime_error("Output stream is not available");
    }
    output_writer_->flush();
  }

  /// @brief Closes the output writer.
  /// This method overrides the base class method to provide filtering functionality.
  /// It ensures that the underlying output writer is also closed.
  auto close() -> void override {
    if (!output_writer_) {
      throw std::runtime_error("Output stream is not available");
    }
    flush();
    output_writer_->close();
  }

 protected:
  std::unique_ptr<AbstractWriter> output_writer_;
};
}  // namespace fox