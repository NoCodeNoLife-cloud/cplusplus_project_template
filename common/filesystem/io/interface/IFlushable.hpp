#pragma once
namespace common {
class IFlushable abstract {
 public:
  virtual ~IFlushable() = default;
  virtual auto flush() -> void = 0;
};
}  // namespace common
