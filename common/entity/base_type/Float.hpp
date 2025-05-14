#pragma once
#include <string>
#include <entity/base_type/Object.hpp>
#include <io/interface/IBoostSerializable.hpp>

namespace common {
  class Float final : public Object, public IBoostSerializable<Float> {
  public:
    static constexpr float POSITIVE_INFINITY = std::numeric_limits<float>::infinity();
    static constexpr float NEGATIVE_INFINITY = -std::numeric_limits<float>::infinity();
    static constexpr float NaN = std::numeric_limits<float>::quiet_NaN();
    static constexpr float MAX_VALUE = std::numeric_limits<float>::max();
    static constexpr float MIN_VALUE = std::numeric_limits<float>::min();
    explicit Float(float value);
    ~Float() override;
    Float(const Float& other);
    Float(Float&& other) noexcept;
    Float& operator=(const Float& other);
    Float& operator=(Float&& other) noexcept;
    explicit operator float() const;
    [[nodiscard]] auto hashCode() const -> size_t override;
    [[nodiscard]] auto toString() const -> std::string override;
    [[nodiscard]] auto floatValue() const -> float;
    static auto parseFloat(const std::string& str) -> Float;
    auto operator<=>(const Float& other) const -> std::partial_ordering;
    auto operator==(const Float& other) const -> bool;
    auto operator+(const Float& other) const -> Float;
    auto operator-(const Float& other) const -> Float;
    auto operator*(const Float& other) const -> Float;
    auto operator/(const Float& other) const -> Float;

  private:
    friend std::formatter<Float>;
    friend class boost::serialization::access;
    float value_{0.0};
    template <class Archive>
    auto serialize(Archive& ar, unsigned int version) -> void;
  };

  template <class Archive>
  auto Float::serialize(Archive& ar, const unsigned int version) -> void {
    ar & value_;
  }
}

template <>
struct std::formatter<common::Float> : common::GenericFormatter<common::Float, &common::Float::value_> {};
