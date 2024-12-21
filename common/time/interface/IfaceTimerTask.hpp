#pragma once
namespace common::time::iface {
/// \brief Abstract class for objects that can be scheduled to be executed by a Timer.
/// \details The class provides a single method, `execute()`, which must be implemented by any derived class.
/// The `execute()` method is called by the Timer when the timer interval expires.
class IfaceTimerTask {
public:
  virtual ~IfaceTimerTask() = default;
  virtual void execute() = 0;
};
}
