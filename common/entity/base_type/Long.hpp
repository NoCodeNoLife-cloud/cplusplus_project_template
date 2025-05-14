#pragma once
#include <string>
#include <entity/base_type/Object.hpp>
#include <io/interface/IBoostSerializable.hpp>

namespace common {
  class Long final : public Object, IBoostSerializable<Long> {
  public:
    static constexpr int64_t MAX_VALUE = std::numeric_limits<int64_t>::max();
    static constexpr int64_t MIN_VALUE = std::numeric_limits<int64_t>::min();
    explicit Long(int64_t value = 0l);
    ~Long() override;
    Long(const Long& other);
    Long(Long&& other) noexcept;
    Long& operator=(const Long& other);
    Long& operator=(Long&& other) noexcept;
    explicit operator int64_t() const;
    [[nodiscard]] auto hashCode() const -> size_t override;
    [[nodiscard]] auto toString() const -> std::string override;
    [[nodiscard]] auto longValue() const -> int64_t;
    static auto parseLong(const std::string& str) -> Long;
    auto operator<=>(const Long& other) const -> std::partial_ordering;
    auto operator==(const Long& other) const -> bool;
    auto operator+(const Long& other) const -> Long;
    auto operator-(const Long& other) const -> Long;
    auto operator*(const Long& other) const -> Long;
    auto operator/(const Long& other) const -> Long;
    auto operator%(const Long& other) const -> Long;

  private:
    friend std::formatter<Long>;
    friend class boost::serialization::access;
    int64_t value_{0};
    template <class Archive>
    auto serialize(Archive& ar, unsigned int version) -> void;
  };

  template <class Archive>
  auto Long::serialize(Archive& ar, const unsigned int version) -> void {
    ar & value_;
  }
}

template <>
struct std::formatter<common::Long> : common::GenericFormatter<common::Long, &common::Long::value_> {};
