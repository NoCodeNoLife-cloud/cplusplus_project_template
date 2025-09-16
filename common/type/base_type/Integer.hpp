#pragma once
#include <string>
#include <utility>

namespace fox
{
    class Integer
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

    inline auto Integer::intToRoman(const int32_t num) noexcept -> std::string
    {
        std::string roman;
        int32_t remaining = num;
        for (const auto& [value, symbol] : valueSymbols)
        {
            while (remaining >= value)
            {
                remaining -= value;
                roman += symbol;
            }
            if (remaining == 0)
            {
                break;
            }
        }
        return roman;
    }
} // namespace fox
