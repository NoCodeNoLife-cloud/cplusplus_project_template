#pragma once
#include <string>
#include <entity/base_type/Object.hpp>
#include <entity/interface/IComparable.hpp>

namespace common {
  class Byte final : public Object, public IComparable<Byte> {
  public:
    static constexpr uint8_t MIN_VALUE = std::numeric_limits<uint8_t>::min();
    static constexpr uint8_t MAX_VALUE = std::numeric_limits<uint8_t>::max();
    explicit Byte(uint8_t value = 0);
    ~Byte() override;
    [[nodiscard]] auto clone() const -> std::unique_ptr<ICloneable> override;
    explicit operator unsigned char() const;
    [[nodiscard]] auto equals(const Byte& other) const -> bool override;
    [[nodiscard]] auto compareTo(const Byte& other) const -> int32_t override;
    static auto parseByte(const std::string& str) -> Byte;
    [[nodiscard]] auto byteValue() const -> uint8_t;
    auto operator<=>(const Byte& other) const -> std::partial_ordering;
    auto operator+(const Byte& other) const -> Byte;
    auto operator-(const Byte& other) const -> Byte;

  private:
    uint8_t value_{0};
  };
}
