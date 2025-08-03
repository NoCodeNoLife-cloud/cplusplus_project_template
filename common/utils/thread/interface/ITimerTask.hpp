#pragma once
namespace common {
class ITimerTask abstract {
 public:
  virtual ~ITimerTask() = default;

  /// @brief Executes the timer task.
  virtual void execute() = 0;
};
}  // namespace common
