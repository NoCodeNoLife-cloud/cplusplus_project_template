#pragma once
#include <limits>
#include <cmath>

namespace fox
{
    static constexpr std::size_t BITS_PER_CHAR = 0x08;

    /// @brief Parameters for configuring a Bloom filter
    /// This class encapsulates all the parameters needed to configure a Bloom filter,
    /// including size constraints, hash function counts, and optimization parameters.
    /// It provides functionality to compute optimal parameters based on expected element
    /// count and desired false positive probability.
    class BloomParameters final
    {
    public:
        BloomParameters() noexcept;

        ~BloomParameters();

        auto operator!() const noexcept -> bool;

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

        /// @brief Optimal parameters computed for the bloom filter
        /// This structure holds the computed optimal number of hash functions
        /// and table size based on the projected element count and false positive probability.
        struct optimal_parameters_t
        {
            optimal_parameters_t() noexcept;

            uint32_t number_of_hashes;
            uint64_t table_size;
        };

        optimal_parameters_t optimal_parameters;
        /// @brief Computes the optimal parameters for the bloom filter based on the
        ///        projected element count and false positive probability.
        /// @return true if the parameters were successfully computed, false otherwise.
        auto compute_optimal_parameters() -> bool;
    };

    inline BloomParameters::BloomParameters() noexcept : minimum_size(1),
                                                         maximum_size(std::numeric_limits<uint64_t>::max()),
                                                         minimum_number_of_hashes(1),
                                                         maximum_number_of_hashes(std::numeric_limits<uint32_t>::max()),
                                                         projected_element_count(10000),
                                                         false_positive_probability(
                                                             1.0 / static_cast<double>(projected_element_count)),
                                                         random_seed(0xA5A5A5A55A5A5A5AULL)
    {
    }

    inline BloomParameters::~BloomParameters() = default;

    inline auto BloomParameters::operator!() const noexcept -> bool
    {
        return minimum_size > maximum_size || minimum_number_of_hashes > maximum_number_of_hashes ||
            minimum_number_of_hashes < 1 || 0 == maximum_number_of_hashes || 0 == projected_element_count ||
            false_positive_probability < 0.0 ||
            std::numeric_limits<double>::infinity() == std::abs(false_positive_probability) || 0 == random_seed ||
            0xFFFFFFFFFFFFFFFFULL == random_seed;
    }

    inline BloomParameters::optimal_parameters_t::optimal_parameters_t() noexcept : number_of_hashes(0), table_size(0)
    {
    }

    inline auto BloomParameters::compute_optimal_parameters() -> bool
    {
        if (!*this)
            return false;

        double min_m = std::numeric_limits<double>::infinity();
        double min_k = 0.0;
        double k = 1.0;

        while (k < 1000.0)
        {
            const double numerator = -k * static_cast<double>(projected_element_count);
            const double denominator = std::log(1.0 - std::pow(false_positive_probability, 1.0 / k));

            if (const double curr_m = numerator / denominator; curr_m < min_m)
            {
                min_m = curr_m;
                min_k = k;
            }

            k += 1.0;
        }

        optimal_parameters_t& parameters = optimal_parameters;

        parameters.number_of_hashes = static_cast<uint32_t>(min_k);

        parameters.table_size = static_cast<uint64_t>(min_m);

        parameters.table_size +=
            parameters.table_size % BITS_PER_CHAR != 0 ? BITS_PER_CHAR - parameters.table_size % BITS_PER_CHAR : 0;

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
}
