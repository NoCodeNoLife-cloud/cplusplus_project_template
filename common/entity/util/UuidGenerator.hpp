#pragma once
#include <cstdint>
#include <iomanip>
#include <random>
#include <sstream>
#include <string>
#include <vector>
#include "entity/interface/IfaceComparable.hpp"

namespace common::entity::util {
/// \brief A class that represents a universally unique identifier (UUID).
/// \details  A UUID is a 128-bit value that is used to identify information in computer systems.
/// It is usually represented as a 32-character hexadecimal string, with 8 characters
/// for the most significant 60 bits, a hyphen, 4 characters for the next 16 bits,
/// a hyphen, 4 characters for the next 12 bits, a hyphen, and finally 12 characters
/// for the least significant 48 bits.
class UuidGenerator final : public iface::IfaceComparable<UuidGenerator> {
public:
  UuidGenerator() = default;

  UuidGenerator(const uint64_t mostSigBits, const uint64_t leastSigBits) : mostSignificantBits(mostSigBits), leastSignificantBits(leastSigBits) {}

  ~UuidGenerator() override = default;

  /// \brief Generates a random UUID.
  /// \return a random UUID.
  static auto randomUUID() -> UuidGenerator {
    return {generateRandom64Bits(), generateRandom64Bits()};
  }

  /// \brief Converts a string to a UUID.
  /// \param name The string to be converted.
  /// \return The UUID represented by the string.
  /// \details The string must be in the format of 8-4-4-4-12, otherwise, an exception will be thrown.
  static auto fromString(const std::string& name) -> UuidGenerator {
    uint64_t msb = 0;
    uint64_t lsb = 0;
    size_t idx = 0;
    for (const char c : name) {
      if (c == '-') continue;
      const uint64_t hexValue = c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10;
      if (idx < 16) {
        msb = msb << 4 | hexValue;
      }
      else {
        lsb = lsb << 4 | hexValue;
      }
      ++idx;
    }
    return {msb, lsb};
  }

  /// \brief Returns the most significant bits of the UUID.
  /// \return The most significant 64 bits of the UUID.
  [[nodiscard]] auto getMostSignificantBits() const -> uint64_t {
    return mostSignificantBits;
  }

  /// \brief Returns the least significant bits of the UUID.
  /// \return The least significant 64 bits of the UUID.
  [[nodiscard]] auto getLeastSignificantBits() const -> uint64_t {
    return leastSignificantBits;
  }

  /// \brief Converts the UUID to a string.
  /// \return The string representation of the UUID, in the format of 8-4-4-4-12.
  [[nodiscard]] auto toString() const -> std::string {
    std::ostringstream oss;
    oss << std::hex << std::setfill('0') << std::setw(8) << (mostSignificantBits >> 32) << '-' << std::setw(4) << (mostSignificantBits >> 16 & 0xFFFF) << '-' << std::setw(4) << (mostSignificantBits & 0xFFFF) << '-' << std::setw(4) << (leastSignificantBits >> 48) << '-' << std::setw(12) << (leastSignificantBits & 0xFFFFFFFFFFFFULL);
    return oss.str();
  }

  /// \brief Checks if the UUID is equal to another UUID.
  /// \param other The UUID to compare with.
  /// \return True if the UUIDs are equal.
  [[nodiscard]] auto equals(const UuidGenerator& other) const -> bool override {
    return mostSignificantBits == other.mostSignificantBits && leastSignificantBits == other.leastSignificantBits;
  }

  /// \brief Compares the UUID with another UUID.
  /// \param other The UUID to compare with.
  /// \return A negative integer, zero, or a positive integer as the UUID is less than, equal to, or greater than the
  /// other UUID.
  [[nodiscard]] auto compareTo(const UuidGenerator& other) const -> int override {
    if (mostSignificantBits < other.mostSignificantBits) return -1;
    if (mostSignificantBits > other.mostSignificantBits) return 1;
    if (leastSignificantBits < other.leastSignificantBits) return -1;
    if (leastSignificantBits > other.leastSignificantBits) return 1;
    return 0;
  }

  /// \brief Returns a hash code for the UUID.
  /// \return A hash code for the UUID.
  [[nodiscard]] auto hashCode() const -> int {
    return static_cast<int>(mostSignificantBits >> 32 ^ mostSignificantBits ^ leastSignificantBits >> 32 ^ leastSignificantBits);
  }

  /// \brief Converts a byte array to a UUID.
  /// \param name The byte array to be converted.
  /// \return The UUID represented by the byte array.
  /// \details The byte array is hashed using the std::hash function and the 128-bit hash value is used to create a UUID.
  static auto nameUUIDFromBytes(const std::vector<unsigned char>& name) -> UuidGenerator {
    constexpr std::hash<std::string> hashFn;
    const std::string data(name.begin(), name.end());
    const size_t hashValue = hashFn(data);
    return {static_cast<uint64_t>(hashValue), (hashValue >> 32)};
  }

private:
  uint64_t mostSignificantBits{};
  uint64_t leastSignificantBits{};

  /// \brief Generates a random 64-bit value.
  /// \return A random 64-bit value.
  static auto generateRandom64Bits() -> uint64_t {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> dis;
    return dis(gen);
  }
};
}
