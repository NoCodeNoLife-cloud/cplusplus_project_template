#pragma once
#include <entity/base_type/Object.hpp>
#include <entity/interface/IComparable.hpp>

namespace common {
  class Short final : public Object, public IComparable<Short> {
  public:
    static constexpr int16_t MAX_VALUE = std::numeric_limits<int16_t>::max();
    static constexpr int16_t MIN_VALUE = std::numeric_limits<int16_t>::min();
    explicit Short(int16_t value);
    ~Short() override;
    [[nodiscard]] auto clone() const -> std::unique_ptr<ICloneable> override;
    explicit operator short() const;
    [[nodiscard]] auto toString() const -> std::string override;
    [[nodiscard]] auto shortValue() const -> int16_t;
    [[nodiscard]] auto equals(const Short& other) const -> bool override;
    [[nodiscard]] auto compareTo(const Short& other) const -> int32_t override;
    static auto parseShort(const std::string& str) -> Short;
    auto operator<=>(const Short& other) const -> std::partial_ordering;
    auto operator+(const Short& other) const -> Short;
    auto operator-(const Short& other) const -> Short;
    auto operator*(const Short& other) const -> Short;
    auto operator/(const Short& other) const -> Short;
    auto operator%(const Short& other) const -> Short;

  private:
    int16_t value_{0};
    friend std::formatter<Short>;
  };
}

template <>
struct std::formatter<common::Short> : common::GenericFormatter<common::Short, &common::Short::value_> {};
