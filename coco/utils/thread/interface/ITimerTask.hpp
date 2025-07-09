#pragma once
namespace coco
{
    class ITimerTask abstract
    {
    public:
        virtual ~ITimerTask() = default;
        virtual void execute() = 0;
    };
}
