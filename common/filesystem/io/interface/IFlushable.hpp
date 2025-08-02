#pragma once
namespace common {
class IFlushable abstract {
 public:
  virtual ~IFlushable() = default;

  /// @brief Flush the stream
  virtual auto flush() -> void = 0;
};
}  // namespace common
