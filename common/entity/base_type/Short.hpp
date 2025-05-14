#pragma once
#include <string>
#include <entity/base_type/Object.hpp>
#include <io/interface/IBoostSerializable.hpp>

namespace common {
  class Short final : public Object, public IBoostSerializable<Short> {
  public:
    static constexpr int16_t MAX_VALUE = std::numeric_limits<int16_t>::max();
    static constexpr int16_t MIN_VALUE = std::numeric_limits<int16_t>::min();
    explicit Short(int16_t value);
    ~Short() override;
    Short(const Short& other);
    Short(Short&& other) noexcept;
    Short& operator=(const Short& other);
    Short& operator=(Short&& other) noexcept;
    explicit operator short() const;
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
    friend class boost::serialization::access;
    int16_t value_{0};
    template <class Archive>
    auto serialize(Archive& ar, unsigned int version) -> void;
  };

  template <class Archive>
  auto Short::serialize(Archive& ar, const unsigned int version) -> void {
    ar & value_;
  }
}

template <>
struct std::formatter<common::Short> : common::GenericFormatter<common::Short, &common::Short::value_> {};
