#pragma once
#include <type_traits>
#include <mutex>
#include <stdexcept>

namespace fox
{
    /// @brief A wrapper class for static object initialization and management.
    /// Ensures thread-safe initialization of static objects with lazy initialization support.
    /// @tparam T The type of object to wrap
    template <typename T>
    class StaticObjectWrapper
    {
    public:
        StaticObjectWrapper() = delete;
        StaticObjectWrapper(const StaticObjectWrapper&) = delete;
        StaticObjectWrapper& operator=(const StaticObjectWrapper&) = delete;

        /// @brief Initialize the static object with provided arguments
        /// @tparam Args Types of arguments to forward to T's constructor
        /// @param args Arguments to forward to T's constructor
        template <typename... Args>
        static void init(Args&&... args) noexcept
        {
            std::call_once(init_flag_, construct<Args...>, std::forward<Args>(args)...);
        }

        /// @brief Get a mutable reference to the static object
        /// @return Reference to the static object
        /// @throws std::runtime_error if object was not initialized and is not default constructible
        static auto get() -> T&
        {
            if constexpr (std::is_default_constructible_v<T>)
            {
                std::call_once(init_flag_, []
                {
                    instance_ = new T();
                });
            }

            if (!instance_)
            {
                throw std::runtime_error(
                    "StaticObjectWrapper: Object not initialized. "
                    "Call init() with required parameters before first use."
                );
            }
            return *instance_;
        }

        /// @brief Destroy the static object if it exists
        static void destroy() noexcept
        {
            if (instance_)
            {
                delete instance_;
                instance_ = nullptr;
            }
        }

    private:
        static inline T* instance_ = nullptr;
        static inline std::once_flag init_flag_;

        /// @brief Construct the object with provided arguments
        /// @tparam Args Types of arguments to forward to T's constructor
        /// @param args Arguments to forward to T's constructor
        template <typename... Args>
        static void construct(Args&&... args)
        {
            instance_ = new T(std::forward<Args>(args)...);
        }
    };
}
