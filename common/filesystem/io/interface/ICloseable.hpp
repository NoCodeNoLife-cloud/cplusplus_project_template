#pragma once

namespace fox {
/// @brief Interface for resources that can be closed.
/// This interface defines a common contract for closing resources such as files, streams, or connections.
/// Implementing classes must provide a mechanism to properly release or close the associated resource.
class ICloseable {
 public:
  /// @brief Virtual destructor to ensure proper cleanup of derived classes
  virtual ~ICloseable() = default;

  /// @brief Close the resource.
  /// This method should release any system resources held by the implementing class.
  /// After calling this method, the resource should no longer be usable.
  virtual auto close() -> void = 0;
};
}  // namespace fox
