#include "src/toolkit/ObjectFactory.hpp"

#include <memory>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>

namespace common
{
    template <typename T>
    template <typename V, typename... Args>
    auto ObjectFactory<T>::registerType(const std::string& type_name,
                                        Args&&... args)
        -> void
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
    auto ObjectFactory<T>::createObject(const std::string& type_name)
        -> std::unique_ptr<T>
    {
        auto it = registry_.find(type_name);
        if (it != registry_.end())
        {
            return it->second();
        }
        throw std::runtime_error("Unknown type: " + type_name);
    }

    template <typename T>
    auto ObjectFactory<T>::execute() noexcept
        -> bool
    {
        registerAll();
        return true;
    }
}
