#pragma once
#include <entity/base_type/Object.hpp>
#include <entity/interface/IComparable.hpp>

namespace common {
  class Integer final : public Object, public IComparable<Integer> {
  public:
    static constexpr int32_t MIN_VALUE = std::numeric_limits<int32_t>::min();
    static constexpr int32_t MAX_VALUE = std::numeric_limits<int32_t>::max();
    explicit Integer(int32_t value = 0);
    ~Integer() override;
    explicit operator int32_t() const;
    [[nodiscard]] std::string toString() const override;
    [[nodiscard]] auto intValue() const -> int32_t;
    static auto parseInt(const std::string& str) -> Integer;
    [[nodiscard]] auto compareTo(const Integer& other) const -> int32_t override;
    [[nodiscard]] bool equals(const Integer& other) const override;
    auto operator<=>(const Integer& other) const -> std::partial_ordering;
    auto operator+(const Integer& other) const -> Integer;
    auto operator-(const Integer& other) const -> Integer;
    auto operator*(const Integer& other) const -> Integer;
    auto operator/(const Integer& other) const -> Integer;

  private:
    friend std::formatter<Integer>;
    int32_t value_{0};
  };
}

template <>
struct std::formatter<common::Integer> : common::GenericFormatter<common::Integer, &common::Integer::value_> {};
