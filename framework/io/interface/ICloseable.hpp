#pragma once
namespace framework::iface {
  class ICloseable abstract {
  public:
    virtual ~ICloseable() = default;
    virtual auto close() -> void = 0;
  };
}
