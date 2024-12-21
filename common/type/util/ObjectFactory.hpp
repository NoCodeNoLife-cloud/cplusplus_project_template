#pragma once
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>

#include "interface/IStartupTask.hpp"

namespace common
{
    template <typename T>
    class ObjectFactory : public service::IStartupTask
    {
    public:
        template <typename V, typename... Args>
        static void registerType(const std::string& type_name, Args&&... args)
        {
            registry[type_name] = [args = std::make_tuple(std::forward<Args>(args)...)]() mutable
            {
                return std::apply(
                    []<typename... T0>(T0&&... inner_args) -> std::unique_ptr<V>
                    {
                        return std::make_unique<V>(std::forward<T0>(inner_args)...);
                    },
                    args
                );
            };
        }

        static std::unique_ptr<T> createObject(const std::string& type_name)
        {
            auto it = registry.find(type_name);
            if (it != registry.end())
            {
                return it->second();
            }
            throw std::runtime_error("Unknown type: " + type_name);
        }

        auto execute() -> bool override
        {
            registerAll();
            return true;
        }

    private:
        virtual auto registerAll() -> void =0;

        static inline std::unordered_map<std::string, std::function<std::unique_ptr<T>()>> registry;
    };
}
