#include "Long.hpp"

#include <stdexcept>
#include <boost/functional/hash.hpp>

namespace common
{
    Long::Long(const int64_t value) : value_(value)
    {
    }

    Long::~Long() = default;

    Long::Long(const Long& other) : value_(other.value_)
    {
    }

    Long::Long(Long&& other) noexcept : value_(other.value_)
    {
    }

    Long& Long::operator=(const Long& other)
    {
        if (this != &other)
        {
            value_ = other.value_;
        }
        return *this;
    }

    Long& Long::operator=(Long&& other) noexcept
    {
        if (this != &other)
        {
            value_ = other.value_;
        }
        return *this;
    }

    size_t Long::hashCode() const
    {
        size_t seed = 0;
        boost::hash_combine(seed, getClass());
        boost::hash_combine(seed, value_);
        return seed;
    }

    std::string Long::toString() const
    {
        return std::format("{}", *this);
    }

    Long::operator int64_t() const
    {
        return value_;
    }

    auto Long::longValue() const -> int64_t
    {
        return value_;
    }

    auto Long::parseLong(const std::string& str) -> Long
    {
        size_t pos = 0;
        const int64_t result = std::stoll(str, &pos, 10);
        if (pos != str.length() || pos == 0)
        {
            throw std::invalid_argument("Invalid input string for Long conversion");
        }
        return Long(result);
    }

    auto Long::operator<=>(const Long& other) const -> std::partial_ordering
    {
        return value_ <=> other.value_;
    }

    auto Long::operator==(const Long& other) const -> bool
    {
        return value_ == other.value_;
    }

    auto Long::operator+(const Long& other) const -> Long
    {
        return Long(this->value_ + other.value_);
    }

    auto Long::operator-(const Long& other) const -> Long
    {
        return Long(this->value_ - other.value_);
    }

    auto Long::operator*(const Long& other) const -> Long
    {
        return Long(this->value_ * other.value_);
    }

    auto Long::operator/(const Long& other) const -> Long
    {
        if (other.value_ == 0)
        {
            throw std::overflow_error("Division by zero");
        }
        return Long(this->value_ / other.value_);
    }

    auto Long::operator%(const Long& other) const -> Long
    {
        if (other.value_ == 0)
        {
            throw std::overflow_error("Modulo by zero");
        }
        return Long(this->value_ % other.value_);
    }
}
