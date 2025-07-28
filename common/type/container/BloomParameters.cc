#include "BloomParameters.hpp"

#include <limits>

namespace common {
BloomParameters::BloomParameters()
    : minimum_size(1),
      maximum_size(std::numeric_limits<uint64_t>::max()),
      minimum_number_of_hashes(1),
      maximum_number_of_hashes(std::numeric_limits<uint32_t>::max()),
      projected_element_count(10000),
      false_positive_probability(1.0 /
                                 static_cast<double>(projected_element_count)),
      random_seed(0xA5A5A5A55A5A5A5AULL) {}

BloomParameters::~BloomParameters() = default;

auto BloomParameters::operator!() const -> bool {
  return minimum_size > maximum_size ||
         minimum_number_of_hashes > maximum_number_of_hashes ||
         minimum_number_of_hashes < 1 || 0 == maximum_number_of_hashes ||
         0 == projected_element_count || false_positive_probability < 0.0 ||
         std::numeric_limits<double>::infinity() ==
             std::abs(false_positive_probability) ||
         0 == random_seed || 0xFFFFFFFFFFFFFFFFULL == random_seed;
}

BloomParameters::optimal_parameters_t::optimal_parameters_t()
    : number_of_hashes(0), table_size(0) {}

auto BloomParameters::compute_optimal_parameters() -> bool {
  if (!*this) return false;

  double min_m = std::numeric_limits<double>::infinity();
  double min_k = 0.0;
  double k = 1.0;

  while (k < 1000.0) {
    const double numerator = -k * static_cast<double>(projected_element_count);
    const double denominator =
        std::log(1.0 - std::pow(false_positive_probability, 1.0 / k));

    if (const double curr_m = numerator / denominator; curr_m < min_m) {
      min_m = curr_m;
      min_k = k;
    }

    k += 1.0;
  }

  optimal_parameters_t& parameters = optimal_parameters;

  parameters.number_of_hashes = static_cast<uint32_t>(min_k);

  parameters.table_size = static_cast<uint64_t>(min_m);

  parameters.table_size +=
      parameters.table_size % BITS_PER_CHAR != 0
          ? BITS_PER_CHAR - parameters.table_size % BITS_PER_CHAR
          : 0;

  if (parameters.number_of_hashes < minimum_number_of_hashes)
    parameters.number_of_hashes = minimum_number_of_hashes;
  else if (parameters.number_of_hashes > maximum_number_of_hashes)
    parameters.number_of_hashes = maximum_number_of_hashes;

  if (parameters.table_size < minimum_size)
    parameters.table_size = minimum_size;
  else if (parameters.table_size > maximum_size)
    parameters.table_size = maximum_size;

  return true;
}
}  // namespace common
