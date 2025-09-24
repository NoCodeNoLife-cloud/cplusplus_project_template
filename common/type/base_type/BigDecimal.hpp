#pragma once
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <stdexcept>
#include <string>
#include <compare>

namespace fox
{
    /// @brief A class for high-precision decimal arithmetic
    /// @details This class uses boost::multiprecision::cpp_dec_float_100 for underlying storage
    ///          to provide high precision decimal operations.
    class BigDecimal
    {
    public:
        explicit BigDecimal(const std::string& str);

        explicit BigDecimal(double num);

        /// @brief Addition operator
        /// @param other The BigDecimal to add
        /// @return The sum of this BigDecimal and other
        auto operator+(const BigDecimal& other) const noexcept -> BigDecimal;

        /// @brief Subtraction operator
        /// @param other The BigDecimal to subtract
        /// @return The difference of this BigDecimal and other
        auto operator-(const BigDecimal& other) const noexcept -> BigDecimal;

        /// @brief Multiplication operator
        /// @param other The BigDecimal to multiply
        /// @return The product of this BigDecimal and other
        auto operator*(const BigDecimal& other) const noexcept -> BigDecimal;

        /// @brief Division operator
        /// @param other The BigDecimal to divide by
        /// @return The quotient of this BigDecimal and other
        auto operator/(const BigDecimal& other) const -> BigDecimal;

        /// @brief Three-way comparison operator
        /// @param other The BigDecimal to compare with
        /// @return std::partial_ordering result of the comparison
        auto operator<=>(const BigDecimal& other) const noexcept -> std::strong_ordering;

        /// @brief Equality comparison operator
        /// @param other The BigDecimal to compare with
        /// @return true if the values are equal, false otherwise
        auto operator==(const BigDecimal& other) const noexcept -> bool;

    private:
        boost::multiprecision::cpp_dec_float_100 value_;
    };

    inline BigDecimal::BigDecimal(const std::string& str) : value_(str)
    {
    }

    inline BigDecimal::BigDecimal(const double num) : value_(num)
    {
    }

    inline auto BigDecimal::operator+(const BigDecimal& other) const noexcept -> BigDecimal
    {
        return BigDecimal((value_ + other.value_).convert_to<std::string>());
    }

    inline auto BigDecimal::operator-(const BigDecimal& other) const noexcept -> BigDecimal
    {
        return BigDecimal((value_ - other.value_).convert_to<std::string>());
    }

    inline auto BigDecimal::operator*(const BigDecimal& other) const noexcept -> BigDecimal
    {
        return BigDecimal((value_ * other.value_).convert_to<std::string>());
    }

    inline auto BigDecimal::operator/(const BigDecimal& other) const -> BigDecimal
    {
        if (other.value_ == 0)
        {
            throw std::invalid_argument("Division by zero is not allowed.");
        }
        return BigDecimal((value_ / other.value_).convert_to<std::string>());
    }

    inline auto BigDecimal::operator<=>(const BigDecimal& other) const noexcept -> std::strong_ordering
    {
        if (value_ < other.value_)
        {
            return std::strong_ordering::less;
        }
        if (value_ > other.value_)
        {
            return std::strong_ordering::greater;
        }
        return std::strong_ordering::equal;
    }

    inline auto BigDecimal::operator==(const BigDecimal& other) const noexcept -> bool
    {
        return value_ == other.value_;
    }
}
