#pragma once
#include <string>
#include <entity/base_type/Object.hpp>

namespace common {
  class Boolean final : public Object {
  public:
    explicit Boolean(bool value = false);
    ~Boolean() override;
    Boolean(const Boolean& other);
    Boolean(Boolean&& other) noexcept;
    Boolean& operator=(const Boolean& other);
    Boolean& operator=(Boolean&& other) noexcept;
    [[nodiscard]] auto hashCode() const -> size_t override;
    [[nodiscard]] auto toString() const -> std::string override;
    explicit operator bool() const;
    [[nodiscard]] auto boolValue() const -> bool;
    static auto parseBoolean(const std::string& str) -> Boolean;
    [[nodiscard]] auto booleanValue() const -> bool;
    auto operator<=>(const Boolean& other) const -> std::partial_ordering;

  private:
    friend std::formatter<Boolean>;
    bool value_{false};
  };

  const Boolean True{true};
  const Boolean False{false};
}

template <>
struct std::formatter<common::Boolean> : common::GenericFormatter<common::Boolean, &common::Boolean::value_> {};
