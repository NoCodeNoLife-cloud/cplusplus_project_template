#include "src/toolkit/EnumToolkit.hpp"

#include <magic_enum/magic_enum.hpp>
#include <string>

namespace fox
{
    template <typename T>
    auto EnumToolkit::getEnumClassName(const T value) noexcept -> std::string
    {
        return static_cast<std::string>(magic_enum::enum_name(value));
    }
}
