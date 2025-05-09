#pragma once
#include <string>
#include <entity/base_type/Object.hpp>

namespace common {
  class Integer final : public Object {
  public:
    static constexpr int32_t MIN_VALUE = std::numeric_limits<int32_t>::min();
    static constexpr int32_t MAX_VALUE = std::numeric_limits<int32_t>::max();
    explicit Integer(int32_t value = 0);
    ~Integer() override;
    [[nodiscard]] auto toString() const -> std::string override;
    explicit operator int32_t() const;
    [[nodiscard]] auto intValue() const -> int32_t;
    static auto parseInt(const std::string& str) -> Integer;
    auto operator<=>(const Integer& other) const -> std::partial_ordering;
    auto operator+(const Integer& other) const -> Integer;
    auto operator-(const Integer& other) const -> Integer;
    auto operator*(const Integer& other) const -> Integer;
    auto operator/(const Integer& other) const -> Integer;

  private:
    int32_t value_{0};
  };
}
