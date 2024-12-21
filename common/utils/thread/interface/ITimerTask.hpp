#pragma once
namespace common
{
    class ITimerTask abstract
    {
    public:
        virtual ~ITimerTask() = default;
        virtual void execute() = 0;
    };
}
