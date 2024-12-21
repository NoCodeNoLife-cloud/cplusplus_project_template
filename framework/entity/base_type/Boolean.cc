#include "Boolean.hpp"

namespace framework::entity::base_type
{

Boolean::Boolean(const bool value) : value_(value)
{
}

Boolean::~Boolean() = default;

Boolean::operator bool() const
{
    return value_;
}

std::string Boolean::toString() const
{
    return std::format("{}", *this);
}

auto Boolean::boolValue() const -> bool
{
    return value_;
}

auto Boolean::compareTo(const Boolean &other) const -> int32_t
{
    return value_ - other.value_;
}

auto Boolean::parseBoolean(const std::string &str) -> Boolean
{
    if (str == "true" || str == "TRUE")
    {
        return Boolean(true);
    }
    if (str == "false" || str == "FALSE")
    {
        return Boolean(false);
    }
    throw std::invalid_argument("Invalid input string for Boolean conversion");
}

auto Boolean::booleanValue() const -> bool
{
    return value_;
}

auto Boolean::equals(const Boolean &other) const -> bool
{
    return value_ == other.value_;
}

auto Boolean::operator==(const Boolean &other) const -> bool
{
    return equals(other);
}

auto Boolean::operator!=(const Boolean &other) const -> bool
{
    return !equals(other);
}

const Boolean TRUE{true};
const Boolean FALSE{false};

} // namespace framework::entity::base_type
