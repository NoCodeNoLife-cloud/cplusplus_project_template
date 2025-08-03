#pragma once
#include <cmath>

namespace common {
static constexpr std::size_t BITS_PER_CHAR = 0x08;

class BloomParameters final {
 public:
  BloomParameters();
  ~BloomParameters();
  auto operator!() const -> bool;
  /// Allowable min/max size of the bloom filter in bits
  uint64_t minimum_size;
  uint64_t maximum_size;
  /// Allowable min/max number of hash functions
  uint32_t minimum_number_of_hashes;
  uint32_t maximum_number_of_hashes;
  /// The approximate number of elements to be inserted
  /// into the bloom filter, should be within one order
  /// of magnitude. The default is 10000.
  uint64_t projected_element_count;
  /// The approximate false positive probability expected
  /// from the bloom filter. The default is assumed to be
  /// the reciprocal of the projected_element_count.
  double false_positive_probability;
  uint64_t random_seed;

  struct optimal_parameters_t {
    optimal_parameters_t();
    uint32_t number_of_hashes;
    uint64_t table_size;
  };

  optimal_parameters_t optimal_parameters;
  /// @brief Computes the optimal parameters for the bloom filter based on the
  ///        projected element count and false positive probability.
  /// @return true if the parameters were successfully computed, false otherwise.
  auto compute_optimal_parameters() -> bool;
};
}  // namespace common
