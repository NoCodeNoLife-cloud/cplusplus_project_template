#pragma once
#include <string>
#include <entity/base_type/Object.hpp>
#include <entity/interface/IComparable.hpp>

namespace common {
  class Boolean final : public Object, public IComparable<Boolean> {
  public:
    explicit Boolean(bool value = false);
    ~Boolean() override;
    [[nodiscard]] auto toString() const -> std::string override;
    explicit operator bool() const;
    [[nodiscard]] auto boolValue() const -> bool;
    [[nodiscard]] auto compareTo(const Boolean& other) const -> int32_t override;
    static auto parseBoolean(const std::string& str) -> Boolean;
    [[nodiscard]] auto booleanValue() const -> bool;
    [[nodiscard]] auto equals(const Boolean& other) const -> bool override;
    auto operator<=>(const Boolean& other) const -> std::partial_ordering;


  private:
    bool value_{false};
  };
  const Boolean True{true};
  const Boolean False{false};
}
