#pragma once
#include <functional>
#include <stdexcept>
#include "interface/IRunnable.hpp"

namespace common::thread
{
    template <typename ReturnType, typename... Args> class TaskWrapper final : public iface::IRunnable<ReturnType, Args...>
    {
    public:
        explicit TaskWrapper(std::function<ReturnType(Args...)> func, std::function<void()> then);
        auto Run(Args... args) -> ReturnType override;
        auto SetMainFunction(std::function<ReturnType(Args...)> func) -> void;
        auto SetThenFunction(std::function<void()> then) -> void;
    private:
        std::function<ReturnType(Args...)> mainFunc_;
        std::function<void()> thenFunc_;
    };

    template <typename ReturnType, typename... Args> TaskWrapper<ReturnType, Args...>::TaskWrapper(std::function<ReturnType(Args...)> func, std::function<void()> then): mainFunc_(std::move(func)), thenFunc_(std::move(then)) {}

    template <typename ReturnType, typename... Args> auto TaskWrapper<ReturnType, Args...>::Run(Args... args) -> ReturnType
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

    template <typename ReturnType, typename... Args> auto TaskWrapper<ReturnType, Args...>::SetMainFunction(std::function<ReturnType(Args...)> func) -> void
    {
        mainFunc_ = std::move(func);
    }

    template <typename ReturnType, typename... Args> auto TaskWrapper<ReturnType, Args...>::SetThenFunction(std::function<void()> then) -> void
    {
        thenFunc_ = std::move(then);
    }
}
