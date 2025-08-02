#pragma once
namespace common {
class ICloseable abstract {
 public:
  virtual ~ICloseable() = default;

  /// @brief Close the resource.
  virtual auto close() -> void = 0;
};
}  // namespace common
