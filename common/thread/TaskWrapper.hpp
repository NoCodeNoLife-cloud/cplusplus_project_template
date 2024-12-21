#pragma once
#include <functional>
#include <stdexcept>
#include "interface/IfaceRunnable.hpp"

namespace common::thread
{
    template <typename ReturnType, typename... Args>
    class TaskWrapper final : public iface::IfaceRunnable<ReturnType, Args...>
    {
    public:
        explicit TaskWrapper(std::function<ReturnType(Args...)> func, std::function<void()> then) :
            mainFunc_(std::move(func)), thenFunc_(std::move(then))
        {
        }

        auto Run(Args... args) -> ReturnType override
        {
            if (!mainFunc_)
            {
                throw std::runtime_error("Main function is not set.");
            }
            ReturnType result = mainFunc_(std::forward<Args>(args)...);
            if (thenFunc_)
            {
                thenFunc_();
            }
            return result;
        }

        auto SetMainFunction(std::function<ReturnType(Args...)> func) -> void
        {
            mainFunc_ = std::move(func);
        }

        auto SetThenFunction(std::function<void()> then) -> void
        {
            thenFunc_ = std::move(then);
        }

    private:
        std::function<ReturnType(Args...)> mainFunc_;
        std::function<void()> thenFunc_;
    };
}
