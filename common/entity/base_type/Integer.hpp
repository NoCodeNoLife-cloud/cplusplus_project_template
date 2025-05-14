#pragma once
#include <string>
#include <entity/base_type/Object.hpp>
#include <io/interface/IBoostSerializable.hpp>

namespace common {
  class Integer final : public Object, public IBoostSerializable<Integer> {
  public:
    static constexpr int32_t MIN_VALUE = std::numeric_limits<int32_t>::min();
    static constexpr int32_t MAX_VALUE = std::numeric_limits<int32_t>::max();
    explicit Integer(int32_t value = 0);
    ~Integer() override;
    Integer(const Integer& other);
    Integer(Integer&& other) noexcept;
    Integer& operator=(const Integer& other);
    Integer& operator=(Integer&& other) noexcept;
    explicit operator int32_t() const;
    [[nodiscard]] auto hashCode() const -> size_t override;
    [[nodiscard]] auto toString() const -> std::string override;
    [[nodiscard]] auto intValue() const -> int32_t;
    static auto parseInt(const std::string& str) -> Integer;
    auto operator<=>(const Integer& other) const -> std::partial_ordering;
    auto operator==(const Integer& other) const -> bool;
    auto operator+(const Integer& other) const -> Integer;
    auto operator-(const Integer& other) const -> Integer;
    auto operator*(const Integer& other) const -> Integer;
    auto operator/(const Integer& other) const -> Integer;

  private:
    friend std::formatter<Integer>;
    friend class boost::serialization::access;
    int32_t value_{0};
    template <class Archive>
    auto serialize(Archive& ar, unsigned int version) -> void;
  };

  template <class Archive>
  auto Integer::serialize(Archive& ar, const unsigned int version) -> void {
    ar & value_;
  }
}

template <>
struct std::formatter<common::Integer> : common::GenericFormatter<common::Integer, &common::Integer::value_> {};
