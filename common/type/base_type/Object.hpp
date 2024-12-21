#pragma once
#include <format>
#include <string>
#include <typeinfo>

#include "utils/format/GenericFormatter.hpp"

namespace common
{
    class Object
    {
    public:
        Object();
        virtual ~Object();
        Object(const Object& other);
        Object(const Object&& other) noexcept;
        Object& operator=(const Object& other);
        Object& operator=(Object&& other) noexcept;
        [[nodiscard]] virtual auto getClass() const -> const std::type_info&;
        [[nodiscard]] virtual auto hashCode() const -> size_t;
        [[nodiscard]] virtual auto toString() const -> std::string;

    private:
        friend std::formatter<Object>;
    };
}

template <>
struct std::formatter<common::Object> : common::GenericFormatter<common::Object>
{
};
