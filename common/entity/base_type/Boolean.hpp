#pragma once
#include <string>
#include <entity/base_type/Object.hpp>

namespace common {
  class Boolean final : public Object {
  public:
    explicit Boolean(bool value = false);
    ~Boolean() override;
    [[nodiscard]] auto toString() const -> std::string override;
    explicit operator bool() const;
    [[nodiscard]] auto boolValue() const -> bool;
    static auto parseBoolean(const std::string& str) -> Boolean;
    [[nodiscard]] auto booleanValue() const -> bool;
    auto operator<=>(const Boolean& other) const -> std::partial_ordering;

  private:
    bool value_{false};
  };
  const Boolean True{true};
  const Boolean False{false};
}
