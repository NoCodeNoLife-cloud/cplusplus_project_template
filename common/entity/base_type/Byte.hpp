#pragma once
#include <format>
#include <iostream>
#include <string>
#include <entity/base_type/Object.hpp>
#include "entity/interface/IfaceComparable.hpp"

namespace common::entity::base_type {
/// \brief A Byte object wraps a value of primitive type byte in an object.
/// \details An object of type Byte contains a single field whose type is byte.
/// The Byte class provides several methods for performing operations on a byte by a Byte object, including methods for
/// adding, subtracting, multiplying, and dividing two Byte objects. There are also methods for determining the absolute
/// value, as well as methods for comparing two Byte objects.
class Byte final : public Object, public iface::IfaceComparable<Byte> {
public:
  static constexpr int8_t MIN_VALUE = std::numeric_limits<int8_t>::min();
  static constexpr int8_t MAX_VALUE = std::numeric_limits<int8_t>::max();

  explicit Byte(const int8_t value = 0): value_(value) {}

  ~Byte() override = default;

  /// \brief Convert the Byte object to a signed char.
  /// \return The underlying int8_t value of the Byte object as a signed char.
  /// \details This operator function allows the Byte object to be implicitly
  ///          converted to a signed char, providing a convenient way to access
  ///          the raw byte value.
  explicit operator signed char() const {
    return value_;
  }

  /// \brief Check if this Byte object is equal to another object.
  /// \param other The other object to compare with.
  /// \return True if the objects are equal, false otherwise.
  /// \details This function compares the underlying byte values.
  /// If the other object is not of type Byte, it returns false.
  [[nodiscard]] auto equals(const Byte& other) const -> bool override {
    return value_ == other.value_;
  }

  /// \brief Compare this Byte object with another.
  /// \param other The Byte object to compare with.
  /// \return An integer less than, equal to, or greater than zero if this object
  /// is considered to be respectively less than, equal to, or greater than the specified object.
  /// \details This function compares the underlying byte values directly.
  [[nodiscard]] auto compareTo(const Byte& other) const -> int override {
    return (value_ > other.value_) - (value_ < other.value_);
  }

  /// \brief Returns a string representation of the object.
  /// \return A string representing the object's type name.
  /// \details This function uses `typeid` to retrieve the name of the object's type.
  [[nodiscard]] auto toString() const -> std::string override {
    return std::format("{}", *this);
  }

  /// \brief Get the byte value of the object.
  /// \return The underlying int8_t value of the Byte object.
  /// \details This function returns the raw byte value stored in the Byte object.
  static auto parseByte(const std::string& str) -> Byte {
    try {
      const int result = std::stoi(str);
      if (result < MIN_VALUE || result > MAX_VALUE) {
        throw std::out_of_range("Value out of range for Byte");
      }
      return Byte(static_cast<int8_t>(result));
    }
    catch (const std::invalid_argument&) {
      throw std::invalid_argument("Invalid input string for Byte conversion");
    } catch (const std::out_of_range&) {
      throw std::out_of_range("Value out of range for Byte");
    }
  }

  /// \brief Get the byte value of the object.
  /// \return The underlying int8_t value of the Byte object.
  /// \details This function returns the raw byte value stored in the Byte object.
  [[nodiscard]] auto byteValue() const -> int8_t {
    return value_;
  }

  /// \brief Check if this Byte object is equal to another Byte object.
  /// \param other The other Byte object to compare with.
  /// \return True if the objects are equal, false otherwise.
  /// \details This function compares the underlying byte values directly.
  auto operator==(const Byte& other) const -> bool {
    return equals(other);
  }

  /// \brief Check if this Byte object is not equal to another Byte object.
  /// \param other The other Byte object to compare with.
  /// \return True if the objects are not equal, false otherwise.
  /// \details This function compares the underlying byte values directly.
  auto operator!=(const Byte& other) const -> bool {
    return !equals(other);
  }

  /// \brief Check if this Byte object is less than another Byte object.
  /// \param other The other Byte object to compare with.
  /// \return True if this Byte object is less than the other Byte object, false otherwise.
  /// \details This function compares the underlying byte values directly.
  auto operator<(const Byte& other) const -> bool {
    return value_ < other.value_;
  }

  /// \brief Check if this Byte object is greater than another Byte object.
  /// \param other The other Byte object to compare with.
  /// \return True if this Byte object is greater than the other Byte object, false otherwise.
  /// \details This function compares the underlying byte values directly.
  auto operator>(const Byte& other) const -> bool {
    return value_ > other.value_;
  }

  /// \brief Check if this Byte object is less than or equal to another Byte object.
  /// \param other The other Byte object to compare with.
  /// \return True if this Byte object is less than or equal to the other Byte object, false otherwise.
  /// \details This function compares the underlying byte values directly.
  auto operator<=(const Byte& other) const -> bool {
    return value_ <= other.value_;
  }

  /// \brief Check if this Byte object is greater than or equal to another Byte object.
  /// \param other The other Byte object to compare with.
  /// \return True if this Byte object is greater than or equal to the other Byte object, false otherwise.
  /// \details This function compares the underlying byte values directly.
  auto operator>=(const Byte& other) const -> bool {
    return value_ >= other.value_;
  }

  /// \brief Add another Byte object to this one.
  /// \param other The other Byte object to add.
  /// \return A new Byte object with the result of the addition.
  /// \details This function adds the underlying byte values directly and checks for overflow.
  auto operator+(const Byte& other) const -> Byte {
    const int result = this->value_ + other.value_;
    if (result < MIN_VALUE || result > MAX_VALUE) {
      throw std::overflow_error("Byte overflow in addition");
    }
    return Byte(static_cast<int8_t>(result));
  }

  /// \brief Subtract another Byte object from this one.
  /// \param other The other Byte object to subtract.
  /// \return A new Byte object with the result of the subtraction.
  /// \details This function subtracts the underlying byte values directly and checks for underflow.
  auto operator-(const Byte& other) const -> Byte {
    const int result = this->value_ - other.value_;
    if (result < MIN_VALUE || result > MAX_VALUE) {
      throw std::overflow_error("Byte overflow in subtraction");
    }
    return Byte(static_cast<int8_t>(result));
  }

private:
  int8_t value_{0};
  friend std::formatter<Byte>;
};
}

template <>
struct std::formatter<common::entity::base_type::Byte> {
  /// \brief Parse the format specifiers for the Byte class.
  /// This function parses the format specifiers for the Byte class.
  /// The format specifiers are as follows:
  /// \param ctx The format parse context.
  /// \return The parsed format specifiers.
  constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator {
    const auto begin = ctx.begin();
    if (const auto end = ctx.end(); begin != end && *begin != '}') {
      throw std::format_error("invalid format");
    }
    return begin;
  }

  /// \brief Format the Byte object into a string.
  /// This function formats the Byte object using the provided format context.
  /// It generates a string representation of the Byte object.
  /// \param content The Byte object to format.
  /// \param ctx The format context to use for formatting.
  /// \return An iterator to the end of the inserted sequence.
  static auto format(const common::entity::base_type::Byte& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>> {
    return std::format_to(ctx.out(), "{}", content.value_);
  }
};

/// \brief Output stream operator for Byte objects.
/// This function inserts the value of the given Byte object into the given output stream.
/// \param os The output stream to insert the value into.
/// \param content The Byte object to insert.
/// \return The output stream after insertion.
inline auto operator<<(std::ostream& os, const common::entity::base_type::Byte& content) -> std::ostream& {
  return os << std::format("{}", content);
}
