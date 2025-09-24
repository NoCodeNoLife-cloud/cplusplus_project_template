#pragma once
#include <magic_enum/magic_enum.hpp>
#include <string>

namespace fox
{
    /// @brief Utility class for enum operations.
    /// This class provides static methods to work with enums,
    /// such as converting enum values to their string representations.
    class EnumToolkit
    {
    public:
        EnumToolkit() = delete;

        /// @brief Get the class name of an enum value as a string.
        /// @tparam T The enum type.
        /// @param value The enum value.
        /// @return std::string The name of the enum value as a string.
        template <typename T>
        [[nodiscard]] static auto getEnumClassName(T value) noexcept -> std::string;
    };

    template <typename T>
    auto EnumToolkit::getEnumClassName(const T value) noexcept -> std::string
    {
        return static_cast<std::string>(magic_enum::enum_name(value));
    }
}
