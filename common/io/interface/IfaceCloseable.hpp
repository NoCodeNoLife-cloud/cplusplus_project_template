#pragma once
namespace common::iface {
/// \brief Abstract interface for objects that can be closed.
/// \details This class declares a method to close the object. Any class that implements
/// this interface must provide a concrete implementation of the close method.
/// The close method is a way to signal to the object that it should release its resources
/// and make any necessary cleanup. The object should be in a valid state before
/// being closed.
class IfaceCloseable abstract {
public:
  virtual ~IfaceCloseable() = default;

  virtual auto close() -> void = 0;
};
}
