#pragma once
#include <string>

#include "Object.hpp"

namespace common {
class Short final : public Object {
 public:
  static constexpr int16_t MAX_VALUE = std::numeric_limits<int16_t>::max();
  static constexpr int16_t MIN_VALUE = std::numeric_limits<int16_t>::min();
  explicit Short(int16_t value);
  ~Short() override;
  Short(const Short& other);
  Short(Short&& other) noexcept;
  Short& operator=(const Short& other);
  Short& operator=(Short&& other) noexcept;
  explicit operator int16_t() const;
  [[nodiscard]] auto hashCode() const -> size_t override;
  [[nodiscard]] auto toString() const -> std::string override;
  [[nodiscard]] auto shortValue() const -> int16_t;
  static auto parseShort(const std::string& str) -> Short;
  auto operator<=>(const Short& other) const -> std::partial_ordering;
  auto operator==(const Short& other) const -> bool;
  auto operator+(const Short& other) const -> Short;
  auto operator-(const Short& other) const -> Short;
  auto operator*(const Short& other) const -> Short;
  auto operator/(const Short& other) const -> Short;
  auto operator%(const Short& other) const -> Short;

 private:
  friend std::formatter<Short>;
  int16_t value_{0};
};
}  // namespace common

template <>
struct std::formatter<common::Short> : common::GenericFormatter<common::Short, &common::Short::value_> {};
