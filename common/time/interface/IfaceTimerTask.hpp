#pragma once
namespace common::time::iface
{
    class IfaceTimerTask
    {
    public:
        virtual ~IfaceTimerTask() = default;
        virtual void execute() = 0;
    };
}
