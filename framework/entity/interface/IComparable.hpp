#pragma once
namespace framework::iface {
  template <typename T>
  class IComparable abstract {
  public:
    virtual ~IComparable() = default;
    [[nodiscard]] virtual auto compareTo(const T& other) const -> int32_t = 0;
    [[nodiscard]] virtual auto equals(const T& other) const -> bool = 0;
  };
}
