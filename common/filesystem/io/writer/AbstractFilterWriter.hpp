#pragma once
#include <memory>

#include "AbstractWriter.hpp"

namespace common {
class AbstractFilterWriter abstract : public AbstractWriter {
 public:
  explicit AbstractFilterWriter(std::unique_ptr<AbstractWriter> outputWriter);
  ~AbstractFilterWriter() override;

  /// @brief Writes a single character to the output writer.
  /// This method overrides the base class method to provide filtering functionality.
  /// The character is processed and then passed to the underlying output writer.
  /// @param c The character to write.
  auto write(char c) -> void override;

  /// @brief Writes a sequence of characters from a vector to the output writer.
  /// This method overrides the base class method to provide filtering functionality.
  /// The characters are processed and then passed to the underlying output writer.
  /// @param cBuf The vector containing the characters to write.
  /// @param off The starting offset in the vector.
  /// @param len The number of characters to write.
  auto write(const std::vector<char>& cBuf, size_t off, size_t len) -> void override;

  /// @brief Writes a sequence of characters from a vector to the output writer.
  /// This method overrides the base class method to provide filtering functionality.
  /// The characters are processed and then passed to the underlying output writer.
  /// @param cBuf The vector containing the characters to write.
  auto write(const std::vector<char>& cBuf) -> void override;

  /// @brief Writes a sequence of characters from a string to the output writer.
  /// This method overrides the base class method to provide filtering functionality.
  /// The characters are processed and then passed to the underlying output writer.
  /// @param str The string containing the characters to write.
  /// @param off The starting offset in the string.
  /// @param len The number of characters to write.
  auto write(const std::string& str, size_t off, size_t len) -> void override;

  /// @brief Writes a sequence of characters from a string to the output writer.
  /// This method overrides the base class method to provide filtering functionality.
  /// The characters are processed and then passed to the underlying output writer.
  /// @param str The string containing the characters to write.
  auto write(const std::string& str) -> void override;

  /// @brief Flushes the output writer.
  /// This method overrides the base class method to provide filtering functionality.
  /// It ensures that any buffered data is written to the underlying output writer.
  auto flush() -> void override;

  /// @brief Closes the output writer.
  /// This method overrides the base class method to provide filtering functionality.
  /// It ensures that the underlying output writer is also closed.
  auto close() -> void override;

 protected:
  std::unique_ptr<AbstractWriter> output_writer_;
};
}  // namespace common
