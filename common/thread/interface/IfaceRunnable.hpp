#pragma once
namespace common::iface
{
    template <typename ReturnType, typename... Args>
    class IfaceRunnable abstract
    {
    public:
        virtual ~IfaceRunnable() = default;
        virtual auto Run(Args... args) -> ReturnType = 0;
    };
}
