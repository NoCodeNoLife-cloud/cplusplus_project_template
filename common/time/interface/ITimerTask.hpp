#pragma once
namespace common::time::iface
{
    class ITimerTask
    {
    public:
        virtual ~ITimerTask() = default;
        virtual void execute() = 0;
    };
}
