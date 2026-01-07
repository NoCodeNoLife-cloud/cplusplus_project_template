#pragma once
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include "src/service/interface/IStartupTask.hpp"

namespace common
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
        /// @throws std::runtime_error If the type name is not registered.
        [[nodiscard]] static auto createObject(const std::string& type_name) -> std::unique_ptr<T>;

        /// @brief Executes the startup task.
        /// @return True if successful, false otherwise.
        [[nodiscard]] auto execute() noexcept -> bool override;

    private:
        /// @brief Registers all types with the factory.
        virtual auto registerAll() -> void = 0;

        static std::unordered_map<std::string, std::function<std::unique_ptr<T>()>> registry_{};
    };
}
