#pragma once
namespace framework {
  class ITimerTask abstract {
  public:
    virtual ~ITimerTask() = default;
    virtual void execute() = 0;
  };
}
