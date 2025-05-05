#include <iomanip>
#include <sstream>
#include <entity/util/UuidGenerator.hpp>

namespace framework::entity::util {
  UuidGenerator::UuidGenerator() = default;

  UuidGenerator::UuidGenerator(const uint64_t mostSigBits, const uint64_t leastSigBits) :
    most_significant_bits_(mostSigBits), least_significant_bits_(leastSigBits) {}

  auto UuidGenerator::randomUUID() -> UuidGenerator {
    return {generateRandom64Bits(), generateRandom64Bits()};
  }

  auto UuidGenerator::fromString(const std::string& name) -> UuidGenerator {
    uint64_t msb = 0;
    uint64_t lsb = 0;
    size_t idx = 0;
    for (const char c : name) {
      if (c == '-')
        continue;
      const uint64_t hexValue = c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10;
      if (idx < 16) {
        msb = msb << 4 | hexValue;
      } else {
        lsb = lsb << 4 | hexValue;
      }
      ++idx;
    }
    return {msb, lsb};
  }

  auto UuidGenerator::getMostSignificantBits() const -> uint64_t {
    return most_significant_bits_;
  }

  auto UuidGenerator::getLeastSignificantBits() const -> uint64_t {
    return least_significant_bits_;
  }

  auto UuidGenerator::toString() const -> std::string {
    std::ostringstream oss;
    oss << std::hex << std::setfill('0') << std::setw(8) << (most_significant_bits_ >> 32) << '-' << std::setw(4)
      << (most_significant_bits_ >> 16 & 0xFFFF) << '-' << std::setw(4) << (most_significant_bits_ & 0xFFFF) << '-'
      << std::setw(4) << (least_significant_bits_ >> 48) << '-' << std::setw(12)
      << (least_significant_bits_ & 0xFFFFFFFFFFFFULL);
    return oss.str();
  }

  auto UuidGenerator::equals(const UuidGenerator& other) const -> bool {
    return most_significant_bits_ == other.most_significant_bits_ &&
      least_significant_bits_ == other.least_significant_bits_;
  }

  auto UuidGenerator::compareTo(const UuidGenerator& other) const -> int32_t {
    if (most_significant_bits_ < other.most_significant_bits_)
      return -1;
    if (most_significant_bits_ > other.most_significant_bits_)
      return 1;
    if (least_significant_bits_ < other.least_significant_bits_)
      return -1;
    if (least_significant_bits_ > other.least_significant_bits_)
      return 1;
    return 0;
  }

  auto UuidGenerator::hashCode() const -> int32_t {
    return static_cast<int32_t>(most_significant_bits_ >> 32 ^ most_significant_bits_ ^ least_significant_bits_ >> 32 ^
      least_significant_bits_);
  }

  auto UuidGenerator::nameUUIDFromBytes(const std::vector<unsigned char>& name) -> UuidGenerator {
    constexpr std::hash<std::string> hashFn;
    const std::string data(name.begin(), name.end());
    const size_t hashValue = hashFn(data);
    return {static_cast<uint64_t>(hashValue), (hashValue >> 32)};
  }

  auto UuidGenerator::generateRandom64Bits() -> uint64_t {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> dis;
    return dis(gen);
  }
} // namespace framework::entity::util
