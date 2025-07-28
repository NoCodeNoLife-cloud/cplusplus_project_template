#pragma once
namespace common {
template <typename ReturnType, typename... Args>
class IRunnable abstract {
 public:
  virtual ~IRunnable() = default;
  virtual auto run(Args... args) -> ReturnType = 0;
};
}  // namespace common
