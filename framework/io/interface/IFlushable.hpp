#pragma once
namespace framework {
  class IFlushable abstract {
  public:
    virtual ~IFlushable() = default;
    virtual auto flush() -> void = 0;
  };
}
