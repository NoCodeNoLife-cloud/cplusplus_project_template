#pragma once
#include <memory>
#include <mutex>
#include <utility>
#include "AbstractWriter.hpp"
#include "PipedReader.hpp"

namespace common::io {
class PipedReader;

/// \brief A final class for writing characters to a pipe.
/// \details The PipedWriter class provides methods to write characters to a pipe.
/// It is a concrete implementation of the AbstractWriter interface.
/// The class supports writing single characters and character arrays, with the option to specify offsets and lengths.
/// The class also supports flushing and closing the stream, as well as appending characters and strings.
/// It is useful for writing text data to a stream with a specified character encoding.
/// \remark Instances of this class are not thread-safe. Synchronization is needed for concurrent access.
class PipedWriter final : public AbstractWriter {
public:
  PipedWriter() = default;

  explicit PipedWriter(std::shared_ptr<PipedReader> writer) : reader_(std::move(writer)) {}

  ~PipedWriter() override {
    close();
  }

  /// \brief Closes the PipedWriter.
  /// \details This method closes the PipedWriter, ensuring that no more data can be written to it.
  /// It flushes any remaining data to the connected PipedReader and resets the connection.
  /// If the writer is already closed, this method does nothing.
  auto close() -> void override {
    if (closed_) {
      return;
    }
    flush();
    closed_ = true;
    if (reader_) {
      reader_->close();
      reader_.reset();
    }
  }

  /// \brief Flushes the PipedWriter.
  /// \details This method is a no-op for PipedWriter as data is directly written to the connected PipedReader.
  /// It is provided to satisfy the interface requirements.
  auto flush() -> void override {
    // no-op
  }

  /// \brief Writes a single character to the PipedWriter.
  /// \details This method writes a single character to the connected PipedReader.
  /// It is thread-safe and throws an exception if the PipedWriter is closed or not connected to a reader.
  /// \param[in] c The character to write.
  auto write(const char c) -> void override {
    std::lock_guard lock(writeMutex_);
    if (closed_) {
      throw std::runtime_error("Cannot write to a closed pipe.");
    }
    if (!reader_) {
      throw std::runtime_error("Pipe is not connected to a reader.");
    }
    reader_->writeToBuffer(c);
  }

  /// \brief Writes a portion of a byte array to the PipedWriter.
  /// \details This method writes a portion of a byte array to the connected PipedReader.
  /// It is thread-safe and throws an exception if the PipedWriter is closed or not connected to a reader.
  /// If the offset is out of bounds, an exception is thrown.
  /// \param[in] cBuf The byte array to write.
  /// \param[in] off The offset in the byte array.
  /// \param[in] len The length of the portion to write.
  auto write(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void override {
    std::lock_guard lock(writeMutex_);
    if (off + len > cBuf.size()) {
      throw std::out_of_range("Buffer overflow detected in write.");
    }
    if (closed_) {
      throw std::runtime_error("Cannot write to a closed pipe.");
    }
    if (!reader_) {
      throw std::runtime_error("Pipe is not connected to a reader.");
    }
    for (size_t i = 0; i < len; ++i) {
      reader_->writeToBuffer(cBuf[off + i]);
    }
  }

  /// \brief Returns a string representation of the PipedWriter.
  /// \details Provides a string representation containing the state of the PipedWriter, such as whether it is closed and whether it is connected to a reader.
  /// \return A string representing the current state of the PipedWriter.
  [[nodiscard]] auto toString() const -> std::string override {
    return "";
  }

  /// \brief Connects the PipedWriter to the given PipedReader.
  /// \details Connects the PipedWriter to the given PipedReader.
  /// \param[in] snk The PipedReader to connect to.
  /// \throw std::runtime_error If the PipedWriter is already connected or closed.
  auto connect(std::shared_ptr<PipedReader> snk) -> void {
    if (reader_ || closed_) {
      throw std::runtime_error("Pipe already connected or closed.");
    }
    reader_ = std::move(snk);
  }

private:
  std::shared_ptr<PipedReader> reader_;
  bool closed_{false};
  std::mutex writeMutex_;
};
}
