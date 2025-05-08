#pragma once
#include <entity/base_type/Object.hpp>
#include <entity/interface/IComparable.hpp>

namespace common {
  class Long final : public Object, public IComparable<Long> {
  public:
    static constexpr int64_t MAX_VALUE = std::numeric_limits<int64_t>::max();
    static constexpr int64_t MIN_VALUE = std::numeric_limits<int64_t>::min();
    explicit Long(int64_t value = 0l);
    ~Long() override;
    explicit operator int64_t() const;
    [[nodiscard]] auto toString() const -> std::string override;
    [[nodiscard]] auto longValue() const -> int64_t;
    [[nodiscard]] auto equals(const Long& other) const -> bool override;
    [[nodiscard]] auto compareTo(const Long& other) const -> int32_t override;
    static auto parseLong(const std::string& str) -> Long;
    auto operator<=>(const Long& other) const -> std::partial_ordering;
    auto operator+(const Long& other) const -> Long;
    auto operator-(const Long& other) const -> Long;
    auto operator*(const Long& other) const -> Long;
    auto operator/(const Long& other) const -> Long;
    auto operator%(const Long& other) const -> Long;

  private:
    int64_t value_{0};
    friend std::formatter<Long>;
  };
}

template <>
struct std::formatter<common::Long> : common::GenericFormatter<common::Long, &common::Long::value_> {};
