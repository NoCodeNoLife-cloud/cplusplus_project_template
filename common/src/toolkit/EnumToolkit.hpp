#pragma once
#include <string>

namespace common
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
}
