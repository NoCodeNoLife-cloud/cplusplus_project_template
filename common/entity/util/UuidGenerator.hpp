#pragma once
#include <cstdint>
#include <iomanip>
#include <random>
#include <sstream>
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
        [[nodiscard]] auto compareTo(const UuidGenerator& other) const -> int override;
        [[nodiscard]] auto hashCode() const -> int;
        static auto nameUUIDFromBytes(const std::vector<unsigned char>& name) -> UuidGenerator;
    private:
        uint64_t mostSignificantBits{};
        uint64_t leastSignificantBits{};
        static auto generateRandom64Bits() -> uint64_t;
    };

    inline UuidGenerator::UuidGenerator() = default;

    inline UuidGenerator::UuidGenerator(const uint64_t mostSigBits, const uint64_t leastSigBits): mostSignificantBits(mostSigBits), leastSignificantBits(leastSigBits) {}



    inline auto UuidGenerator::randomUUID() -> UuidGenerator
    {
        return {generateRandom64Bits(), generateRandom64Bits()};
    }

    inline auto UuidGenerator::fromString(const std::string& name) -> UuidGenerator
    {
        uint64_t msb = 0;
        uint64_t lsb = 0;
        size_t idx = 0;
        for (const char c : name)
        {
            if (c == '-') continue;
            const uint64_t hexValue = c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10;
            if (idx < 16)
            {
                msb = msb << 4 | hexValue;
            }
            else
            {
                lsb = lsb << 4 | hexValue;
            }
            ++idx;
        }
        return {msb, lsb};
    }

    inline auto UuidGenerator::getMostSignificantBits() const -> uint64_t
    {
        return mostSignificantBits;
    }

    inline auto UuidGenerator::getLeastSignificantBits() const -> uint64_t
    {
        return leastSignificantBits;
    }

    inline auto UuidGenerator::toString() const -> std::string
    {
        std::ostringstream oss;
        oss << std::hex << std::setfill('0') << std::setw(8) << (mostSignificantBits >> 32) << '-' << std::setw(4) << (mostSignificantBits >> 16 & 0xFFFF) << '-' << std::setw(4) << (mostSignificantBits & 0xFFFF) << '-' << std::setw(4) << (leastSignificantBits >> 48) << '-' << std::setw(12) << (leastSignificantBits & 0xFFFFFFFFFFFFULL);
        return oss.str();
    }

    inline auto UuidGenerator::equals(const UuidGenerator& other) const -> bool
    {
        return mostSignificantBits == other.mostSignificantBits && leastSignificantBits == other.leastSignificantBits;
    }

    inline auto UuidGenerator::compareTo(const UuidGenerator& other) const -> int
    {
        if (mostSignificantBits < other.mostSignificantBits) return -1;
        if (mostSignificantBits > other.mostSignificantBits) return 1;
        if (leastSignificantBits < other.leastSignificantBits) return -1;
        if (leastSignificantBits > other.leastSignificantBits) return 1;
        return 0;
    }

    inline auto UuidGenerator::hashCode() const -> int
    {
        return static_cast<int>(mostSignificantBits >> 32 ^ mostSignificantBits ^ leastSignificantBits >> 32 ^ leastSignificantBits);
    }

    inline auto UuidGenerator::nameUUIDFromBytes(const std::vector<unsigned char>& name) -> UuidGenerator
    {
        constexpr std::hash<std::string> hashFn;
        const std::string data(name.begin(), name.end());
        const size_t hashValue = hashFn(data);
        return {static_cast<uint64_t>(hashValue), (hashValue >> 32)};
    }

    inline auto UuidGenerator::generateRandom64Bits() -> uint64_t
    {
        std::random_device rd;
        std::mt19937_64 gen(rd());
        std::uniform_int_distribution<uint64_t> dis;
        return dis(gen);
    }
}
