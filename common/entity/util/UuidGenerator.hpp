#pragma once
#include <cstdint>
#include <iomanip>
#include <random>
#include <sstream>
#include <string>
#include <vector>
#include "entity/interface/IfaceComparable.hpp"

namespace common::entity::util
{
    class UuidGenerator final : public iface::IfaceComparable<UuidGenerator>
    {
    public:
        UuidGenerator() = default;

        UuidGenerator(const uint64_t mostSigBits, const uint64_t leastSigBits) : mostSignificantBits(mostSigBits),
                                                                                 leastSignificantBits(leastSigBits)
        {
        }

        ~UuidGenerator() override = default;

        static auto randomUUID() -> UuidGenerator
        {
            return {generateRandom64Bits(), generateRandom64Bits()};
        }

        static auto fromString(const std::string& name) -> UuidGenerator
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

        [[nodiscard]] auto getMostSignificantBits() const -> uint64_t
        {
            return mostSignificantBits;
        }

        [[nodiscard]] auto getLeastSignificantBits() const -> uint64_t
        {
            return leastSignificantBits;
        }

        [[nodiscard]] auto toString() const -> std::string
        {
            std::ostringstream oss;
            oss << std::hex << std::setfill('0') << std::setw(8) << (mostSignificantBits >> 32) << '-' << std::setw(4)
                << (mostSignificantBits >> 16 & 0xFFFF) << '-' << std::setw(4) << (mostSignificantBits & 0xFFFF) << '-'
                << std::setw(4) << (leastSignificantBits >> 48) << '-' << std::setw(12) << (leastSignificantBits &
                    0xFFFFFFFFFFFFULL);
            return oss.str();
        }

        [[nodiscard]] auto equals(const UuidGenerator& other) const -> bool override
        {
            return mostSignificantBits == other.mostSignificantBits && leastSignificantBits == other.
                leastSignificantBits;
        }

        [[nodiscard]] auto compareTo(const UuidGenerator& other) const -> int override
        {
            if (mostSignificantBits < other.mostSignificantBits) return -1;
            if (mostSignificantBits > other.mostSignificantBits) return 1;
            if (leastSignificantBits < other.leastSignificantBits) return -1;
            if (leastSignificantBits > other.leastSignificantBits) return 1;
            return 0;
        }

        [[nodiscard]] auto hashCode() const -> int
        {
            return static_cast<int>(mostSignificantBits >> 32 ^ mostSignificantBits ^ leastSignificantBits >> 32 ^
                leastSignificantBits);
        }

        static auto nameUUIDFromBytes(const std::vector<unsigned char>& name) -> UuidGenerator
        {
            constexpr std::hash<std::string> hashFn;
            const std::string data(name.begin(), name.end());
            const size_t hashValue = hashFn(data);
            return {static_cast<uint64_t>(hashValue), (hashValue >> 32)};
        }

    private:
        uint64_t mostSignificantBits{};
        uint64_t leastSignificantBits{};

        static auto generateRandom64Bits() -> uint64_t
        {
            std::random_device rd;
            std::mt19937_64 gen(rd());
            std::uniform_int_distribution<uint64_t> dis;
            return dis(gen);
        }
    };
}
