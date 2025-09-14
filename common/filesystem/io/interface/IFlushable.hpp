#pragma once

namespace fox {
/// @brief Interface for flushable objects.
/// This interface defines a contract for objects that can be flushed,
/// typically used for streams or buffers that need to ensure all data is written out.
class IFlushable {
 public:
  /// @brief Virtual destructor to ensure proper cleanup of derived classes
  virtual ~IFlushable() = default;

  /// @brief Flush the stream or buffer.
  /// This method ensures that any buffered data is written out to the underlying destination.
  /// Implementation should handle any errors that may occur during the flush operation.
  virtual auto flush() -> void = 0;
};
}  // namespace fox
