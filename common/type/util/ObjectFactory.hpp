#pragma once
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>

#include "service/interface/IStartupTask.hpp"

namespace fox
{
    /// @brief A factory class for creating objects of type T.
    /// @tparam T The base type of objects that this factory can create.
    template <typename T>
    class ObjectFactory : public service::IStartupTask
    {
    public:
        /// @brief Registers a type with the factory.
        /// @tparam V The type to register.
        /// @tparam Args The argument types for the constructor of V.
        /// @param type_name The name to register the type under.
        /// @param args The arguments to forward to the constructor of V.
        template <typename V, typename... Args>
        static auto registerType(const std::string& type_name, Args&&... args) -> void;

        /// @brief Creates an object of the specified type.
        /// @param type_name The name of the type to create.
        /// @return A unique pointer to the created object.
        [[nodiscard]] static auto createObject(const std::string& type_name) -> std::unique_ptr<T>;

        /// @brief Executes the startup task.
        /// @return True if successful, false otherwise.
        auto execute() noexcept -> bool override;

    private:
        /// @brief Registers all types with the factory.
        virtual auto registerAll() -> void = 0;

        static inline std::unordered_map<std::string, std::function<std::unique_ptr<T>()>> registry_;
    };

    template <typename T>
    template <typename V, typename... Args>
    auto ObjectFactory<T>::registerType(const std::string& type_name, Args&&... args) -> void
    {
        registry_[type_name] = [args = std::make_tuple(std::forward<Args>(args)...)]() mutable
        {
            return std::apply(
                []<typename... T0>(T0&&... inner_args) -> std::unique_ptr<V>
                {
                    return std::make_unique<V>(std::forward<T0>(inner_args)...);
                },
                args);
        };
    }

    template <typename T>
    auto ObjectFactory<T>::createObject(const std::string& type_name) -> std::unique_ptr<T>
    {
        auto it = registry_.find(type_name);
        if (it != registry_.end())
        {
            return it->second();
        }
        throw std::runtime_error("Unknown type: " + type_name);
    }

    template <typename T>
    auto ObjectFactory<T>::execute() noexcept -> bool
    {
        registerAll();
        return true;
    }
} // namespace fox
