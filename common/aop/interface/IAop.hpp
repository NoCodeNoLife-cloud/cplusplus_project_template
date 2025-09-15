#pragma once
#include <functional>
#include <type_traits>
#include <utility>

namespace fox
{
    /// @brief Interface class for Aspect-Oriented Programming (AOP) functionalities.
    /// This class provides a template-based interface for implementing AOP concepts
    /// such as before/after method execution advice, exception handling, and result processing.
    /// @tparam Derived The derived class that implements the specific AOP behavior.
    /// The derived class can override the virtual methods to customize the AOP behavior.
    // ReSharper disable once CppTemplateParameterNeverUsed
    template <typename Derived>
    class IAop
    {
    public:
        /// @brief Execute the function with the given arguments
        /// @param func Function to be executed
        /// @param args Arguments to be passed to the function
        /// @return The result of the function
        template <typename Func, typename... Args>
        auto exec(Func&& func, Args&&... args) -> decltype(auto);

        virtual ~IAop() = default;

    private:
        /// @brief Function to be executed before the function call
        virtual auto onEntry() -> void
        {
        }

        /// @brief Function to be executed after the function call
        virtual auto onExit() -> void
        {
        }

        /// @brief Function to be executed when an exception is thrown
        virtual auto onException() -> void
        {
        }

        /// @brief Function to handle the result
        template <typename T>
        auto handleResult(T&& result) -> decltype(auto);
    };

    template <typename Derived>
    template <typename Func, typename... Args>
    auto IAop<Derived>::exec(Func&& func, Args&&... args) -> decltype(auto)
    {
        this->onEntry();
        try
        {
            if constexpr (std::is_void_v<std::invoke_result_t<Func, Args...>>)
            {
                std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
                this->onExit();
            }
            else
            {
                auto result = std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
                this->onExit();
                return static_cast<Derived*>(this)->handleResult(std::move(result));
            }
        }
        catch (...)
        {
            this->onException();
            throw;
        }
    }

    template <typename Derived>
    template <typename T>
    auto IAop<Derived>::handleResult(T&& result) -> decltype(auto)
    {
        return std::forward<T>(result);
    }
} // namespace fox
