#pragma once
#include <functional>

namespace framework::aop::iface {

template <typename Derived>
class IAop abstract {
 public:
  template <typename Func, typename... Args>
  auto exec(Func&& func, Args&&... args) -> decltype(auto) {
    onEntry();
    try {
      if constexpr (std::is_void_v<std::invoke_result_t<Func, Args...>>) {
        std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
        onExit();
      } else {
        auto result = std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
        onExit();
        return static_cast<Derived*>(this)->handleResult(result);
      }
    } catch (...) {
      onException();
      throw;
    }
  }

  virtual ~IAop() = default;

 private:
  virtual void onEntry() {};
  virtual void onExit() {};
  virtual void onException() {};

  template <typename T>
  auto handleResult(T&& result) -> decltype(auto) {
    return std::forward<T>(result);
  }
};
}  // namespace framework::aop::iface
