#pragma once
namespace common
{
/// @brief Interface for flushable objects.
/// This interface defines a contract for objects that can be flushed,
/// typically used for streams or buffers that need to ensure all data is written out.
class IFlushable abstract {
 public:
  virtual ~IFlushable() = default;

  /// @brief Flush the stream
  virtual auto flush() -> void = 0;
};
}  // namespace common
