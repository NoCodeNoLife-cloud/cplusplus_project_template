#pragma once

namespace framework::iface {

template <typename ReturnType, typename... Args>
class IRunnable abstract {
 public:
  virtual ~IRunnable() = default;

  virtual auto Run(Args... args) -> ReturnType = 0;
};

}  // namespace framework::iface
