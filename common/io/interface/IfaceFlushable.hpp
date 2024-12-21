#pragma once
namespace common::iface {
/// \brief Abstract class for objects that can be flushed.
/// \details This abstract class provides the flush method which can be used to flush the content of the object.
class IfaceFlushable abstract {
public:
  virtual ~IfaceFlushable() = default;

  virtual auto flush() -> void = 0;
};
}
