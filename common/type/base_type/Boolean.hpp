#pragma once
#include <string>

#include "Object.hpp"

namespace common {
class Boolean final : public Object {
 public:
  explicit Boolean(bool value = false);
  ~Boolean() override;
  Boolean(const Boolean& other);
  Boolean(Boolean&& other) noexcept;
  explicit operator bool() const;
  Boolean& operator=(const Boolean& other);
  Boolean& operator=(Boolean&& other) noexcept;
  [[nodiscard]] auto hashCode() const -> size_t override;
  [[nodiscard]] auto toString() const -> std::string override;
  [[nodiscard]] auto boolValue() const -> bool;
  static auto parseBoolean(const std::string& str) -> Boolean;
  [[nodiscard]] auto booleanValue() const -> bool;
  auto operator<=>(const Boolean& other) const -> std::partial_ordering;
  auto operator==(const Boolean& other) const -> bool;

 private:
  friend std::formatter<Boolean>;
  bool value_{false};
};

const Boolean True{true};
const Boolean False{false};
}  // namespace common

template <>
struct std::formatter<common::Boolean> : common::GenericFormatter<common::Boolean, &common::Boolean::value_> {};
