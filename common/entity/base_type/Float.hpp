#pragma once
#include <string>
#include <entity/base_type/Object.hpp>

namespace common {
  class Float final : public Object {
  public:
    static constexpr float POSITIVE_INFINITY = std::numeric_limits<float>::infinity();
    static constexpr float NEGATIVE_INFINITY = -std::numeric_limits<float>::infinity();
    static constexpr float NaN = std::numeric_limits<float>::quiet_NaN();
    static constexpr float MAX_VALUE = std::numeric_limits<float>::max();
    static constexpr float MIN_VALUE = std::numeric_limits<float>::min();

    explicit Float(float value);

    ~Float() override;

    [[nodiscard]] auto hashCode() const -> size_t override;

    [[nodiscard]] auto toString() const -> std::string override;

    explicit operator float() const;

    [[nodiscard]] auto floatValue() const -> float;

    static auto parseFloat(const std::string& str) -> Float;

    auto operator<=>(const Float& other) const -> std::partial_ordering;

    auto operator+(const Float& other) const -> Float;

    auto operator-(const Float& other) const -> Float;

    auto operator*(const Float& other) const -> Float;

    auto operator/(const Float& other) const -> Float;

  private:
    float value_{0.0};
  };
}
