#pragma once
#include <fstream>
#include <vector>
#include "interface/IfaceCloseable.hpp"

namespace common::io {
/// \brief Abstract class for input streams.
/// \details This abstract class provides a general interface for input streams.
/// It declares methods for reading from the stream, marking the stream, and resetting the stream.
/// The available method returns the number of bytes that can be read from the stream without blocking.
class AbstractInputStream abstract : public iface::IfaceCloseable {
public:
  ~AbstractInputStream() override = default;

  [[nodiscard]] virtual auto available() -> size_t = 0;

  /// \brief Marks the current position in the stream.
  /// \details This method does nothing as mark is not supported.
  /// \param readLimit The limit of bytes that can be read before the mark position becomes invalid.
  virtual auto mark(int readLimit) -> void {
    throw std::runtime_error("mark not supported");
  }

  /// \brief Tests if this input stream supports the mark and reset methods.
  /// \details Whether this input stream supports the mark and reset methods.
  /// \return true if this input stream supports the mark and reset methods, false otherwise.
  [[nodiscard]] virtual auto markSupported() const -> bool {
    return false;
  }

  virtual auto read() -> std::byte = 0;

  /// \brief Reads bytes into the specified buffer.
  /// \details Attempts to read up to buffer.size() bytes into the provided buffer vector.
  /// \param buffer The buffer into which the data is read.
  /// \return The total number of bytes read into the buffer, or -1 if the end of the stream has been reached.
  virtual auto read(std::vector<std::byte>& buffer) -> size_t {
    return read(buffer, 0, static_cast<int>(buffer.size()));
  }

  /// \brief Reads bytes into the specified buffer.
  /// \details Attempts to read up to len bytes into the provided buffer vector, starting at the offset.
  /// \param buffer The buffer into which the data is read.
  /// \param offset The starting position in the buffer.
  /// \param len The maximum number of bytes to read.
  /// \return The total number of bytes read into the buffer, or -1 if the end of the stream has been reached.
  virtual auto read(std::vector<std::byte>& buffer, const size_t offset, const size_t len) -> size_t {
    if (offset + len > buffer.size()) {
      throw std::out_of_range("Buffer offset/length out of range");
    }
    size_t bytesRead = 0;
    for (int i = 0; i < len; ++i) {
      const std::byte byte = read();
      if (byte == static_cast<std::byte>(-1)) {
        break;
      }
      buffer[offset + i] = static_cast<std::byte>(byte);
      ++bytesRead;
    }
    return bytesRead;
  }

  /// \brief Resets the input stream to the last marked position.
  /// \details This operation is not supported and will throw an exception.
  /// \throws std::runtime_error Always, as reset is not supported by this stream implementation.
  virtual auto reset() -> void {
    throw std::runtime_error("reset not supported");
  }

  /// \brief Skips over and discards n bytes of data from this input stream.
  /// \details The skip method may, for a variety of reasons, end before skipping n bytes.
  /// \param n The number of bytes to skip.
  /// \return The number of bytes actually skipped.
  virtual auto skip(const size_t n) -> size_t {
    size_t skipped = 0;
    for (size_t i = 0; i < n; ++i) {
      if (read() == static_cast<std::byte>(-1)) {
        break;
      }
      ++skipped;
    }
    return skipped;
  }
};
}
