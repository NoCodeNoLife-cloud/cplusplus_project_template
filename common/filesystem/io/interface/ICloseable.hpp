#pragma once
namespace common {
/// @brief Interface for resources that can be closed.
/// This interface defines a common contract for closing resources such as files, streams, or connections.
/// Implementing classes must provide a mechanism to properly release or close the associated resource.
class ICloseable abstract {
 public:
  virtual ~ICloseable() = default;

  /// @brief Close the resource.
  virtual auto close() -> void = 0;
};
}  // namespace common
