#pragma once
namespace framework::iface {
  class IFlushable abstract {
  public:
    virtual ~IFlushable() = default;
    virtual auto flush() -> void = 0;
  };
}
