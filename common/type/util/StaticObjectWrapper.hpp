#pragma once

namespace fox
{
    /// @brief A wrapper class for creating thread-safe singleton instances
    /// This template class provides a thread-safe way to create and access
    /// singleton instances of any type T. The instance is created on first
    /// access and automatically destroyed at program termination.
    template <typename T>
    class StaticObjectWrapper
    {
    public:
        /// @brief Get the unique instance of type T
        /// Returns a reference to the singleton instance of type T.
        /// The instance is created on first call in a thread-safe manner.
        /// @return Reference to the singleton instance
        static auto get_instance() -> T&
        {
            static T instance{};
            return instance;
        }

    private:
        StaticObjectWrapper() = default;
        ~StaticObjectWrapper() = default;
        StaticObjectWrapper(const StaticObjectWrapper&) = delete;
        StaticObjectWrapper(StaticObjectWrapper&&) = delete;
        auto operator=(const StaticObjectWrapper&) -> StaticObjectWrapper& = delete;
        auto operator=(StaticObjectWrapper&&) -> StaticObjectWrapper& = delete;
    };
}
