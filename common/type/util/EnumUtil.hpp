#pragma once
#include <magic_enum/magic_enum.hpp>
#include <string>

namespace fox
{
    /// @brief Utility class for enum operations.
    /// This class provides static methods to work with enums,
    /// such as converting enum values to their string representations.
    class EnumUtil
    {
    public:
        /// @brief Get the class name of an enum value as a string.
        /// @tparam T The enum type.
        /// @param t The enum value.
        /// @return std::string The name of the enum value as a string.
        template <typename T>
        static auto getEnumClassName(T t) -> std::string;
    };

    template <typename T>
    auto EnumUtil::getEnumClassName(T t) -> std::string
    {
        return static_cast<std::string>(magic_enum::enum_name(t));
    }
} // namespace fox
