#include "src/type/base_type/Integer.hpp"

#include <string>
#include <utility>

namespace fox
{
    auto Integer::intToRoman(const int32_t num) noexcept -> std::string
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
}
