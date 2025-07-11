#pragma once
#include <string>
#include <type/base_type/Object.hpp>

namespace coco
{
    class Byte final : public Object
    {
    public:
        static constexpr uint8_t MIN_VALUE = std::numeric_limits<uint8_t>::min();
        static constexpr uint8_t MAX_VALUE = std::numeric_limits<uint8_t>::max();
        explicit Byte(uint8_t value = 0);
        ~Byte() override;
        Byte(const Byte& other);
        Byte(Byte&& other) noexcept;
        Byte& operator=(const Byte& other);
        Byte& operator=(Byte&& other) noexcept;
        explicit operator uint8_t() const;
        [[nodiscard]] auto hashCode() const -> size_t override;
        [[nodiscard]] auto toString() const -> std::string override;
        static auto parseByte(const std::string& str) -> Byte;
        [[nodiscard]] auto byteValue() const -> uint8_t;
        auto operator<=>(const Byte& other) const -> std::partial_ordering;
        auto operator==(const Byte& other) const -> bool;
        auto operator+(const Byte& other) const -> Byte;
        auto operator-(const Byte& other) const -> Byte;

    private:
        friend std::formatter<Byte>;
        uint8_t value_{0};
    };
}

template <>
struct std::formatter<coco::Byte> : coco::GenericFormatter<coco::Byte, &coco::Byte::value_>
{
};
