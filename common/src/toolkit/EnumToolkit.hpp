#pragma once
#include <string>
#include <magic_enum/magic_enum.hpp>

namespace common::toolkit
{
    /// @brief Utility class for enum operations.
    /// This class provides static methods to work with enums,
    /// such as converting enum values to their string representations.
    class EnumToolkit
    {
    public:
        EnumToolkit() = delete;

        /// @brief Get the name of an enum value as a string.
        /// @tparam T The enum type.
        /// @param value The enum value.
        /// @return std::string The name of the enum value as a string.
        template <typename T>
        [[nodiscard]] static auto getEnumName(T value) noexcept -> std::string;

        /// @brief Get the class name of an enum type as a string.
        /// @tparam T The enum type.
        /// @return std::string The name of the enum type as a string.
        template <typename T>
        [[nodiscard]] static auto getEnumTypeName() noexcept -> std::string;

        /// @brief Convert a string to an enum value.
        /// @tparam T The enum type.
        /// @param name The string name of the enum value.
        /// @return Optional containing the enum value if found, otherwise empty optional.
        template <typename T>
        [[nodiscard]] static auto stringToEnum(const std::string& name) noexcept -> std::optional<T>;
    };

    template <typename T>
    auto EnumToolkit::getEnumName(T value) noexcept -> std::string
    {
        return static_cast<std::string>(magic_enum::enum_name(value));
    }

    template <typename T>
    auto EnumToolkit::getEnumTypeName() noexcept -> std::string
    {
        return static_cast<std::string>(magic_enum::enum_type_name<T>());
    }

    template <typename T>
    auto EnumToolkit::stringToEnum(const std::string& name) noexcept -> std::optional<T>
    {
        return magic_enum::enum_cast<T>(name);
    }
}
