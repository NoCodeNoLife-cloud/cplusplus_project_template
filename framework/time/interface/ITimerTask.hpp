#pragma once
namespace framework::time::iface {
  class ITimerTask abstract {
  public:
    virtual ~ITimerTask() = default;
    virtual void execute() = 0;
  };
}
