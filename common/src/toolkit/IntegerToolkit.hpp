#pragma once
#include <string>
#include <utility>

namespace common
{
    /// @brief A utility class for integer operations
    /// @details Provides various integer conversion and manipulation functions
    class IntegerToolkit
    {
        static const inline std::pair<int32_t, std::string> valueSymbols[] = {
            {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"}, {90, "XC"}, {50, "L"},
            {40, "XL"}, {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"},
        };

    public:
        /// @brief Converts an integer to its Roman numeral representation
        /// @param num The integer to convert (must be between 1 and 3999)
        /// @return The Roman numeral representation as a string
        [[nodiscard]] static auto intToRoman(int32_t num) noexcept -> std::string;
    };
}
