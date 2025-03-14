#include "Byte.hpp"

namespace common::entity::base_type
{
    Byte::Byte(const int8_t value): value_(value) {}

    Byte::~Byte() = default;

    Byte::operator signed char() const
    {
        return value_;
    }

    auto Byte::equals(const Byte& other) const -> bool
    {
        return value_ == other.value_;
    }

    auto Byte::compareTo(const Byte& other) const -> int32_t
    {
        return (value_ > other.value_) - (value_ < other.value_);
    }

    std::string Byte::toString() const
    {
        return std::format("{}", *this);
    }

    auto Byte::parseByte(const std::string& str) -> Byte
    {
        try
        {
            const int32_t result = std::stoi(str);
            if (result < MIN_VALUE || result > MAX_VALUE)
            {
                throw std::out_of_range("Value out of range for Byte");
            }
            return Byte(static_cast<int8_t>(result));
        }
        catch (const std::invalid_argument&)
        {
            throw std::invalid_argument("Invalid input string for Byte conversion");
        } catch (const std::out_of_range&)
        {
            throw std::out_of_range("Value out of range for Byte");
        }
    }

    auto Byte::byteValue() const -> int8_t
    {
        return value_;
    }

    auto Byte::operator==(const Byte& other) const -> bool
    {
        return equals(other);
    }

    auto Byte::operator!=(const Byte& other) const -> bool
    {
        return !equals(other);
    }

    auto Byte::operator<(const Byte& other) const -> bool
    {
        return value_ < other.value_;
    }

    auto Byte::operator>(const Byte& other) const -> bool
    {
        return value_ > other.value_;
    }

    auto Byte::operator<=(const Byte& other) const -> bool
    {
        return value_ <= other.value_;
    }

    auto Byte::operator>=(const Byte& other) const -> bool
    {
        return value_ >= other.value_;
    }

    auto Byte::operator+(const Byte& other) const -> Byte
    {
        const int32_t result = this->value_ + other.value_;
        if (result < MIN_VALUE || result > MAX_VALUE)
        {
            throw std::overflow_error("Byte overflow in addition");
        }
        return Byte(static_cast<int8_t>(result));
    }

    auto Byte::operator-(const Byte& other) const -> Byte
    {
        const int32_t result = this->value_ - other.value_;
        if (result < MIN_VALUE || result > MAX_VALUE)
        {
            throw std::overflow_error("Byte overflow in subtraction");
        }
        return Byte(static_cast<int8_t>(result));
    }
}
