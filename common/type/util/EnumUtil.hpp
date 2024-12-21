#pragma once
#include <string>
#include <magic_enum/magic_enum.hpp>

namespace common
{
    class EnumUtil
    {
    public:
        template <typename T>
        static auto getEnumClassName(T t) -> std::string;
    };

    template <typename T>
    auto EnumUtil::getEnumClassName(T t) -> std::string
    {
        return static_cast<std::string>(magic_enum::enum_name(t));
    }
}
