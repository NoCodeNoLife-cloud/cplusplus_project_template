#pragma once
#include <string>
#include <entity/base_type/Object.hpp>

namespace common {
  class Byte final : public Object {
  public:
    static constexpr uint8_t MIN_VALUE = std::numeric_limits<uint8_t>::min();
    static constexpr uint8_t MAX_VALUE = std::numeric_limits<uint8_t>::max();

    explicit Byte(uint8_t value = 0);

    ~Byte() override;

    [[nodiscard]] auto hashCode() const -> size_t override;

    [[nodiscard]] auto toString() const -> std::string override;

    explicit operator unsigned char() const;

    static auto parseByte(const std::string& str) -> Byte;

    [[nodiscard]] auto byteValue() const -> uint8_t;

    auto operator<=>(const Byte& other) const -> std::partial_ordering;

    auto operator+(const Byte& other) const -> Byte;

    auto operator-(const Byte& other) const -> Byte;

  private:
    friend std::formatter<Byte>;
    uint8_t value_{0};
  };
}

template <>
struct std::formatter<common::Byte> : common::GenericFormatter<common::Byte, &common::Byte::value_> {};
