#pragma once
#include <boost/multiprecision/cpp_int.hpp>
#include <string>
#include <compare>
#include <stdexcept>

namespace fox
{
    /// @brief A class representing a big integer using boost::multiprecision::cpp_int
    class BigInteger
    {
    public:
        /// @brief Default constructor, initializes to zero
        BigInteger() noexcept;

        /// @brief Constructs a BigInteger from a string representation
        /// @param str The string representation of the integer
        explicit BigInteger(const std::string& str);

        /// @brief Constructs a BigInteger from an int64_t value
        /// @param num The int64_t value to convert
        explicit BigInteger(int64_t num) noexcept;

        /// @brief Addition operator
        /// @param other The BigInteger to add
        /// @return The result of the addition
        [[nodiscard]] auto operator+(const BigInteger& other) const noexcept -> BigInteger;

        /// @brief Subtraction operator
        /// @param other The BigInteger to subtract
        /// @return The result of the subtraction
        [[nodiscard]] auto operator-(const BigInteger& other) const noexcept -> BigInteger;

        /// @brief Multiplication operator
        /// @param other The BigInteger to multiply
        /// @return The result of the multiplication
        [[nodiscard]] auto operator*(const BigInteger& other) const noexcept -> BigInteger;

        /// @brief Division operator
        /// @param other The BigInteger to divide by
        /// @return The result of the division
        /// @throws std::invalid_argument If attempting to divide by zero
        [[nodiscard]] auto operator/(const BigInteger& other) const -> BigInteger;

        /// @brief Modulus operator
        /// @param other The BigInteger to modulo by
        /// @return The result of the modulus operation
        /// @throws std::invalid_argument If attempting to modulo by zero
        [[nodiscard]] auto operator%(const BigInteger& other) const -> BigInteger;

        /// @brief Three-way comparison operator
        /// @param other The BigInteger to compare with
        /// @return The result of the comparison
        [[nodiscard]] auto operator<=>(const BigInteger& other) const noexcept -> std::strong_ordering;

        /// @brief Equality comparison operator
        /// @param other The BigInteger to compare with
        /// @return true if the values are equal, false otherwise
        [[nodiscard]] auto operator==(const BigInteger& other) const noexcept -> bool;

        /// @brief Create a BigInteger from a string
        /// @param str The string to convert
        /// @return The resulting BigInteger
        [[nodiscard]] static auto fromString(const std::string& str) -> BigInteger;

        /// @brief Create a BigInteger from an int64_t
        /// @param num The int64_t to convert
        /// @return The resulting BigInteger
        [[nodiscard]] static auto fromInt(int64_t num) noexcept -> BigInteger;

    private:
        boost::multiprecision::cpp_int value_{};
    };

    inline BigInteger::BigInteger() noexcept : value_(0)
    {
    }

    inline BigInteger::BigInteger(const std::string& str) : value_(str)
    {
    }

    inline BigInteger::BigInteger(const int64_t num) noexcept : value_(num)
    {
    }

    inline auto BigInteger::operator+(const BigInteger& other) const noexcept -> BigInteger
    {
        return BigInteger((value_ + other.value_).convert_to<std::string>());
    }

    inline auto BigInteger::operator-(const BigInteger& other) const noexcept -> BigInteger
    {
        return BigInteger((value_ - other.value_).convert_to<std::string>());
    }

    inline auto BigInteger::operator*(const BigInteger& other) const noexcept -> BigInteger
    {
        return BigInteger((value_ * other.value_).convert_to<std::string>());
    }

    inline auto BigInteger::operator/(const BigInteger& other) const -> BigInteger
    {
        if (other.value_ == 0)
        {
            throw std::invalid_argument("Division by zero");
        }
        return BigInteger((value_ / other.value_).convert_to<std::string>());
    }

    inline auto BigInteger::operator%(const BigInteger& other) const -> BigInteger
    {
        if (other.value_ == 0)
        {
            throw std::invalid_argument("Modulo by zero");
        }
        return BigInteger((value_ % other.value_).convert_to<std::string>());
    }

    inline auto BigInteger::operator<=>(const BigInteger& other) const noexcept -> std::strong_ordering
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

    inline auto BigInteger::operator==(const BigInteger& other) const noexcept -> bool
    {
        return value_ == other.value_;
    }

    inline auto BigInteger::fromString(const std::string& str) -> BigInteger
    {
        return BigInteger(str);
    }

    inline auto BigInteger::fromInt(const int64_t num) noexcept -> BigInteger
    {
        return BigInteger(num);
    }
}
