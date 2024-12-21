#pragma once
#include <cstdint>
#include <random>
#include <string>
#include <vector>
#include "entity/interface/IComparable.hpp"

namespace common::entity::util
{
    class UuidGenerator final : public iface::IComparable<UuidGenerator>
    {
    public:
        UuidGenerator();
        UuidGenerator(uint64_t mostSigBits, uint64_t leastSigBits);
        ~UuidGenerator() override = default;
        static auto randomUUID() -> UuidGenerator;
        static auto fromString(const std::string& name) -> UuidGenerator;
        [[nodiscard]] auto getMostSignificantBits() const -> uint64_t;
        [[nodiscard]] auto getLeastSignificantBits() const -> uint64_t;
        [[nodiscard]] auto toString() const -> std::string;
        [[nodiscard]] auto equals(const UuidGenerator& other) const -> bool override;
        [[nodiscard]] auto compareTo(const UuidGenerator& other) const -> int32_t override;
        [[nodiscard]] auto hashCode() const -> int32_t;
        static auto nameUUIDFromBytes(const std::vector<unsigned char>& name) -> UuidGenerator;
    private:
        uint64_t mostSignificantBits{};
        uint64_t leastSignificantBits{};
        static auto generateRandom64Bits() -> uint64_t;
    };
}
