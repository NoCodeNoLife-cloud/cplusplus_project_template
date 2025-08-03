#pragma once

namespace service {
class IStartupTask abstract {
 public:
  virtual ~IStartupTask() = default;

  /// @brief Executes the startup task.
  /// @return True if the task was executed successfully, false otherwise.
  virtual auto execute() -> bool = 0;
};
}  // namespace service
