#pragma once
#include <string>
#include <entity/base_type/Object.hpp>
#include <io/interface/IBoostSerializable.hpp>

namespace common {
  class Boolean final : public Object, public IBoostSerializable<Boolean> {
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
    friend class boost::serialization::access;
    bool value_{false};
    template <class Archive>
    auto serialize(Archive& ar, unsigned int version) -> void;
  };

  template <class Archive>
  auto Boolean::serialize(Archive& ar, const unsigned int version) -> void {
    ar & value_;
  }

  const Boolean True{true};
  const Boolean False{false};
}

template <>
struct std::formatter<common::Boolean> : common::GenericFormatter<common::Boolean, &common::Boolean::value_> {};
