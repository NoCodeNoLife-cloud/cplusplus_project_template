#pragma once
#include <functional>

namespace common {
// ReSharper disable once CppTemplateParameterNeverUsed
template <typename Derived>
class IAop abstract {
 public:
  /// @brief Execute the function with the given arguments
  /// @param func Function to be executed
  /// @param args Arguments to be passed to the function
  /// @return The result of the function
  template <typename Func, typename... Args>
  auto exec(Func&& func, Args&&... args) -> decltype(auto);

  virtual ~IAop();

 private:
  /// @brief Function to be executed before the function call
  virtual auto onEntry() -> void;
  /// @brief Function to be executed after the function call
  virtual auto onExit() -> void;
  /// @brief Function to be executed when an exception is thrown
  virtual auto onException() -> void;

  /// @brief Function to handle the result
  template <typename T>
  auto handleResult(T&& result) -> decltype(auto);
};

template <typename Derived>
template <typename Func, typename... Args>
auto IAop<Derived>::exec(Func&& func, Args&&... args) -> decltype(auto) {
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

template <typename Derived>
IAop<Derived>::~IAop() = default;

template <typename Derived>
auto IAop<Derived>::onEntry() -> void {}

template <typename Derived>
auto IAop<Derived>::onExit() -> void {}

template <typename Derived>
auto IAop<Derived>::onException() -> void {}

template <typename Derived>
template <typename T>
auto IAop<Derived>::handleResult(T&& result) -> decltype(auto) {
  return std::forward<T>(result);
}
}  // namespace common
