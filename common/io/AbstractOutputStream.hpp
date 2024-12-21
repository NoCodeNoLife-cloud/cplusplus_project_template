#pragma once
#include <format>
#include <vector>
#include "interface/IfaceCloseable.hpp"
#include "interface/IfaceFlushable.hpp"

namespace common::io {
/// \brief Abstract class for objects that can be written to.
/// \details This class provides an interface for objects that can be written to.
/// It is a base class for classes that implement output streams.
/// It is an abstract class that cannot be instantiated.
class AbstractOutputStream abstract : public iface::IfaceCloseable, public iface::IfaceFlushable {
public:
  ~AbstractOutputStream() override = default;

  virtual auto write(std::byte b) -> void = 0;

  /// \brief Writes the entire buffer to the output stream.
  /// \param buffer The buffer to be written.
  /// \details This function writes the entire buffer to the output stream.
  virtual auto write(const std::vector<std::byte>& buffer) -> void {
    write(buffer, 0, static_cast<int>(buffer.size()));
  }

  /// \brief Writes a portion of the buffer to the output stream.
  /// \param buffer The buffer to be written.
  /// \param offset The starting offset in the buffer.
  /// \param len The number of bytes to be written.
  /// \details This function writes \p len bytes from the buffer starting at \p offset to the output stream.
  virtual auto write(const std::vector<std::byte>& buffer, const size_t offset, const size_t len) -> void {
    if (offset + len > buffer.size()) {
      throw std::out_of_range("Buffer offset/length out of range");
    }
    for (int i = 0; i < len; ++i) {
      write(buffer[offset + i]);
    }
  }
};
}
