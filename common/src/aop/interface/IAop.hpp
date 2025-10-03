#pragma once
#include <functional>
#include <type_traits>
#include <utility>
#include <exception>

namespace common
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

    protected:
        /// @brief Function to be executed before the function call
        /// @details This method is called before the target function is invoked.
        /// Derived classes can override this to implement pre-execution logic.
        virtual void onEntry() = 0;

        /// @brief Function to be executed after the function call
        /// @details This method is called after the target function is successfully invoked.
        /// Derived classes can override this to implement post-execution logic.
        virtual void onExit() = 0;

        /// @brief Function to be executed when an exception is thrown
        /// @details This method is called when an exception is caught during function execution.
        /// Derived classes can override this to implement exception handling logic.
        virtual void onException(std::exception_ptr e) = 0;

        /// @brief Function to handle the result
        /// @tparam T The type of the result
        /// @param result The result to be handled
        /// @return The processed result
        /// @details This method is called to process the result of the function execution.
        /// Derived classes can override this to implement result processing logic.
        template <typename T>
        auto handleResult(T&& result) -> decltype(auto);
    };

    template <typename Derived>
    template <typename Func, typename... Args>
    auto IAop<Derived>::exec(Func&& func, Args&&... args) -> decltype(auto)
    {
        static_cast<Derived*>(this)->onEntry();
        try
        {
            if constexpr (std::is_void_v<std::invoke_result_t<Func, Args...>>)
            {
                std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
                static_cast<Derived*>(this)->onExit();
            }
            else
            {
                auto result = std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
                static_cast<Derived*>(this)->onExit();
                return static_cast<Derived*>(this)->handleResult(std::move(result));
            }
        }
        catch (...)
        {
            static_cast<Derived*>(this)->onException(std::current_exception());
            throw;
        }
    }

    template <typename Derived>
    template <typename T>
    auto IAop<Derived>::handleResult(T&& result) -> decltype(auto)
    {
        return std::forward<T>(result);
    }
}
