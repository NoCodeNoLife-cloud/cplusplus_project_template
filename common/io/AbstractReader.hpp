#pragma once
#include <vector>
#include "interface/IfaceCloseable.hpp"
#include "interface/IfaceReadable.hpp"

namespace common::io {
/// \brief Abstract class for reading character streams.
/// \details The Reader class provides an interface for reading character streams. It is an abstract class that implements
/// the Closeable and Readable interfaces, requiring derived classes to implement methods for reading characters into
/// buffers, marking, and resetting the stream. The class also provides methods to check if marking is supported,
/// determine if the stream is ready to be read, and skip characters.
class AbstractReader abstract : public iface::IfaceCloseable, public iface::IfaceReadable {
public:
  ~AbstractReader() override = default;

  /// \brief Reads a single character.
  /// \details Reads a single character from the reader and returns it. If the end of the stream has been reached, -1 is
  /// returned.
  /// \return The character read, or -1 if the end of the stream has been reached.
  auto read() -> int override {
    std::vector<char> buffer(1);
    if (const size_t bytesRead = read(buffer, 0, 1); bytesRead == -1) {
      return -1;
    }
    return buffer[0];
  }

  virtual auto read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t = 0;

  /// \brief Reads characters into a buffer.
  /// \details Reads characters into the specified buffer, starting at the beginning of the buffer.
  /// \param cBuf The buffer into which the data is read.
  /// \return The total number of characters read into the buffer, or -1 if the end of the stream has been reached.
  virtual auto read(std::vector<char>& cBuf) -> size_t {
    return read(cBuf, 0, static_cast<int>(cBuf.size()));
  }

  /// \brief Tests if this reader supports the mark and reset methods.
  /// \details Whether this reader supports the mark and reset methods.
  /// \return true if this reader supports the mark and reset methods, false otherwise.
  [[nodiscard]] virtual auto markSupported() const -> bool {
    return false;
  }

  virtual auto mark(size_t readAheadLimit) -> void =0;

  virtual auto reset() -> void =0;

  /// \brief Tests if this reader is ready to be read.
  /// \details Whether this reader is ready to be read.
  /// \return true if this reader is ready to be read, false otherwise.
  [[nodiscard]] virtual auto ready() const -> bool {
    return true;
  }

  /// \brief Skips over and discards n characters of data from this reader.
  /// \details The skip method may, for a variety of reasons, end before skipping n characters.
  /// \param n The number of characters to skip.
  /// \return The number of characters actually skipped.
  /// \throws std::invalid_argument If the skip value is negative.
  virtual auto skip(const size_t n) -> size_t {
    size_t skipped = 0;
    while (skipped < n) {
      std::vector<char> buffer(1024);
      const size_t toRead = std::min(n - skipped, buffer.size());
      const size_t readCount = read(buffer, 0, static_cast<int>(toRead));
      if (readCount == -1) break;
      skipped += readCount;
    }
    return skipped;
  }
};
}
