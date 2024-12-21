#pragma once
namespace common::iface {
/// \class IfaceComparable
/// \brief Abstract interface for comparable objects.
template <typename T>
class IfaceComparable abstract {
public:
  virtual ~IfaceComparable() = default;

  [[nodiscard]] virtual auto compareTo(const T& other) const -> int = 0;

  [[nodiscard]] virtual auto equals(const T& other) const -> bool = 0;
};
}
