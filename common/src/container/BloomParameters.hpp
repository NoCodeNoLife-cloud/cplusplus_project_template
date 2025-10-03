#pragma once
#include <cmath>

namespace common
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

        ~BloomParameters() = default;

        /// @brief Checks if the Bloom parameters are valid.
        /// @return True if the parameters are invalid, false otherwise.
        [[nodiscard]] auto operator!() const noexcept -> bool;

        /// @brief Computes the optimal parameters for the bloom filter based on the
        ///        projected element count and false positive probability.
        /// @return true if the parameters were successfully computed, false otherwise.
        auto compute_optimal_parameters() -> bool;

        /// Allowable min/max size of the bloom filter in bits
        uint64_t minimum_size{};
        uint64_t maximum_size{};
        /// Allowable min/max number of hash functions
        uint32_t minimum_number_of_hashes{};
        uint32_t maximum_number_of_hashes{};
        /// The approximate number of elements to be inserted
        /// into the bloom filter, should be within one order
        /// of magnitude. The default is 10000.
        uint64_t projected_element_count{};
        /// The approximate false positive probability expected
        /// from the bloom filter. The default is assumed to be
        /// the reciprocal of the projected_element_count.
        double false_positive_probability{};
        uint64_t random_seed{};

        /// @brief Optimal parameters computed for the bloom filter
        /// This structure holds the computed optimal number of hash functions
        /// and table size based on the projected element count and false positive probability.
        struct optimal_parameters_t
        {
            optimal_parameters_t() noexcept;

            uint32_t number_of_hashes{};
            uint64_t table_size{};
        };

        optimal_parameters_t optimal_parameters{};

    private:
        /// @brief Computes natural logarithm with error handling
        /// @param value The value to compute logarithm for
        /// @return The natural logarithm of value, or 0 if value is non-positive
        [[nodiscard]] static auto safe_log(double value) noexcept -> double;
    };
}
