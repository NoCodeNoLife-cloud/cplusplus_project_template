#pragma once
#include <functional>
#include <stdexcept>
#include "interface/IfaceRunnable.hpp"

namespace common::thread {
/// \brief A wrapper for tasks that can be executed with a main function and an optional then function.
/// \tparam ReturnType The return type of the main function.
/// \tparam Args The types of the arguments for the main function.
/// \details This class provides functionality to set and run a main function with specified arguments,
/// and optionally execute a then function after the main function completes. It extends the Runnable
/// interface, allowing it to be used in contexts where a Runnable is expected.
template <typename ReturnType, typename... Args>
class TaskWrapper final : public iface::IfaceRunnable<ReturnType, Args...> {
public:
  /// \brief TaskWrapper constructors
  /// \param func Main function
  /// \param then Then function. It is called after the main function is finished.
  explicit TaskWrapper(std::function<ReturnType(Args...)> func, std::function<void()> then) : mainFunc_(std::move(func)), thenFunc_(std::move(then)) {}

  /// \brief Run the main function with the given arguments and run the then function after the main function is finished.
  /// \param args Arguments for the main function.
  /// \return The return value of the main function.
  auto Run(Args... args) -> ReturnType override {
    if (!mainFunc_) {
      throw std::runtime_error("Main function is not set.");
    }
    ReturnType result = mainFunc_(std::forward<Args>(args)...);
    if (thenFunc_) {
      thenFunc_();
    }
    return result;
  }

  /// \brief Set the main function to be called.
  /// \param func The main function to be called.
  auto SetMainFunction(std::function<ReturnType(Args...)> func) -> void {
    mainFunc_ = std::move(func);
  }

  /// \brief Set the then function to be called after the main function is finished.
  /// \param then The then function to be called.
  auto SetThenFunction(std::function<void()> then) -> void {
    thenFunc_ = std::move(then);
  }

private:
  std::function<ReturnType(Args...)> mainFunc_;
  std::function<void()> thenFunc_;
};
}
