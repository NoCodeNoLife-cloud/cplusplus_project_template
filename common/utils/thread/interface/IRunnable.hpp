#pragma once
namespace common {
template <typename ReturnType, typename... Args>
class IRunnable abstract {
 public:
  virtual ~IRunnable() = default;

  /// @brief Runs the task with given arguments and returns a value of ReturnType.
  /// @param args Arguments to pass to the task.
  /// @return ReturnType The result of the task execution.
  virtual auto run(Args... args) -> ReturnType = 0;
};
}  // namespace common
