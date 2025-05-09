#pragma once
#include <string>
#include <entity/base_type/Object.hpp>

namespace common {
  class Short final : public Object {
  public:
    static constexpr int16_t MAX_VALUE = std::numeric_limits<int16_t>::max();
    static constexpr int16_t MIN_VALUE = std::numeric_limits<int16_t>::min();
    explicit Short(int16_t value);
    ~Short() override;
    explicit operator short() const;
    [[nodiscard]] auto shortValue() const -> int16_t;
    static auto parseShort(const std::string& str) -> Short;
    auto operator<=>(const Short& other) const -> std::partial_ordering;
    auto operator+(const Short& other) const -> Short;
    auto operator-(const Short& other) const -> Short;
    auto operator*(const Short& other) const -> Short;
    auto operator/(const Short& other) const -> Short;
    auto operator%(const Short& other) const -> Short;

  private:
    int16_t value_{0};
  };
}
