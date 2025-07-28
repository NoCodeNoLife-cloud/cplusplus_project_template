#pragma once
#include <string>
#include <vector>

#include "BloomParameters.hpp"

namespace common {
static const unsigned char bit_mask[BITS_PER_CHAR] = {
    0x01,  // 00000001
    0x02,  // 00000010
    0x04,  // 00000100
    0x08,  // 00001000
    0x10,  // 00010000
    0x20,  // 00100000
    0x40,  // 01000000
    0x80   // 10000000
};

class BloomFilter final {
 protected:
  typedef uint32_t bloom_type_;
  typedef unsigned char cell_type_;
  typedef std::vector<unsigned char> table_type_;

 public:
  BloomFilter();
  explicit BloomFilter(const BloomParameters& p);
  BloomFilter(const BloomFilter& filter);
  auto operator==(const BloomFilter& f) const -> bool;
  auto operator!=(const BloomFilter& f) const -> bool;
  auto operator=(const BloomFilter& f) -> BloomFilter&;
  virtual ~BloomFilter();
  auto operator!() const -> bool;
  auto clear() -> void;
  auto insert(const unsigned char* key_begin, const std::size_t& length)
      -> void;
  template <typename T>
  auto insert(const T& t) -> void;
  auto insert(const std::string& key) -> void;
  auto insert(const char* data, const std::size_t& length) -> void;
  template <typename InputIterator>
  auto insert(InputIterator begin, InputIterator end) -> void;
  auto contains(const unsigned char* key_begin, std::size_t length) const
      -> bool;
  template <typename T>
  auto contains(const T& t) const -> bool;
  [[nodiscard]] auto contains(const std::string& key) const -> bool;
  auto contains(const char* data, const std::size_t& length) const -> bool;
  template <typename InputIterator>
  auto contains_all(InputIterator begin, InputIterator end) const
      -> InputIterator;
  template <typename InputIterator>
  auto contains_none(InputIterator begin, InputIterator end) const
      -> InputIterator;
  [[nodiscard]] auto size() const -> uint64_t;
  [[nodiscard]] auto element_count() const -> uint64_t;
  [[nodiscard]] auto effective_fpp() const -> double;
  auto operator&=(const BloomFilter& f) -> BloomFilter&;
  auto operator|=(const BloomFilter& f) -> BloomFilter&;
  auto operator^=(const BloomFilter& f) -> BloomFilter&;
  [[nodiscard]] auto table() const -> const cell_type_*;
  [[nodiscard]] auto hash_count() const -> std::size_t;

 protected:
  auto compute_indices(const bloom_type_& hash, std::size_t& bit_index,
                       std::size_t& bit) const -> void;
  auto generate_unique_salt() -> void;
  static auto hash_ap(const unsigned char* begin, std::size_t remaining_length,
                      bloom_type_ hash) -> bloom_type_;
  std::vector<bloom_type_> salt_;
  std::vector<unsigned char> bit_table_;
  uint32_t salt_count_{};
  uint64_t table_size_{};
  uint64_t projected_element_count_{};
  uint64_t inserted_element_count_{};
  uint64_t random_seed_{};
  double desired_false_positive_probability_{};
};

inline BloomFilter operator&(const BloomFilter& a, const BloomFilter& b) {
  BloomFilter result = a;
  result &= b;
  return result;
}

inline BloomFilter operator|(const BloomFilter& a, const BloomFilter& b) {
  BloomFilter result = a;
  result |= b;
  return result;
}

inline BloomFilter operator^(const BloomFilter& a, const BloomFilter& b) {
  BloomFilter result = a;
  result ^= b;
  return result;
}
}  // namespace common
