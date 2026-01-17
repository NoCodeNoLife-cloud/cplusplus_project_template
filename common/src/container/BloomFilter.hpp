#pragma once
#include <random>
#include <string>
#include <vector>

#include "BloomParameters.hpp"

namespace common::container
{
    static constexpr unsigned char bit_mask[8] = {
        0x01, // 00000001
        0x02, // 00000010
        0x04, // 00000100
        0x08, // 00001000
        0x10, // 00010000
        0x20, // 00100000
        0x40, // 01000000
        0x80 // 10000000
    };

    /// @brief A Bloom filter implementation for probabilistic set membership testing.
    /// A Bloom filter is a space-efficient probabilistic data structure that is used to test
    /// whether an element is a member of a set. False positive matches are possible, but false
    /// negatives are not. In other words, a query returns either "possibly in set" or "definitely
    /// not in set".
    /// The Bloom filter uses multiple hash functions to map elements to positions in a bit array.
    /// When adding an element, the corresponding bits are set to 1. When querying for an element,
    /// if any of the corresponding bits are 0, the element is definitely not in the set.
    class BloomFilter final
    {
    private:
        using bloom_type_ = uint32_t;
        using cell_type_ = unsigned char;
        using table_type_ = std::vector<unsigned char>;

    public:
        BloomFilter() = default;

        explicit BloomFilter(const BloomParameters& p) noexcept;

        BloomFilter(const BloomFilter& filter) = default;

        ~BloomFilter() = default;

        /// @brief Compares two Bloom filters for equality.
        /// @param f The Bloom filter to compare with.
        /// @return True if the filters are equal, false otherwise.
        [[nodiscard]] auto operator==(const BloomFilter& f) const noexcept -> bool;

        /// @brief Compares two Bloom filters for inequality.
        /// @param f The Bloom filter to compare with.
        /// @return True if the filters are not equal, false otherwise.
        [[nodiscard]] auto operator!=(const BloomFilter& f) const noexcept -> bool;

        /// @brief Assigns one Bloom filter to another.
        /// @param f The Bloom filter to assign from.
        /// @return A reference to the assigned Bloom filter.
        auto operator=(const BloomFilter& f) -> BloomFilter& = default;

        /// @brief Checks if the Bloom filter is empty.
        /// @return True if the filter is empty, false otherwise.
        [[nodiscard]] auto operator!() const noexcept -> bool;

        /// @brief Performs bitwise AND operation with another Bloom filter.
        /// @param f The Bloom filter to perform AND with.
        /// @return A reference to the current Bloom filter.
        auto operator&=(const BloomFilter& f) -> BloomFilter&;

        /// @brief Performs bitwise OR operation with another Bloom filter.
        /// @param f The Bloom filter to perform OR with.
        /// @return A reference to the current Bloom filter.
        auto operator|=(const BloomFilter& f) -> BloomFilter&;

        /// @brief Performs bitwise XOR operation with another Bloom filter.
        /// @param f The Bloom filter to perform XOR with.
        /// @return A reference to the current Bloom filter.
        auto operator^=(const BloomFilter& f) -> BloomFilter&;

        /// @brief Clears all elements from the Bloom filter.
        auto clear() noexcept -> void;

        /// @brief Inserts a key into the Bloom filter.
        /// @param key_begin Pointer to the beginning of the key.
        /// @param length Length of the key.
        auto insert(const unsigned char* key_begin, std::size_t length) -> void;

        /// @brief Inserts a key into the Bloom filter.
        /// @tparam T Type of the key.
        /// @param t The key to insert.
        template <typename T>
        auto insert(const T& t) -> void;

        /// @brief Inserts a string key into the Bloom filter.
        /// @param key The string key to insert.
        auto insert(const std::string& key) -> void;

        /// @brief Inserts a key into the Bloom filter.
        /// @param data Pointer to the beginning of the key.
        /// @param length Length of the key.
        auto insert(const char* data, std::size_t length) -> void;

        /// @brief Inserts a range of keys into the Bloom filter.
        /// @tparam InputIterator Type of the input iterator.
        /// @param begin Iterator to the beginning of the range.
        /// @param end Iterator to the end of the range.
        template <typename InputIterator>
        auto insert(InputIterator begin, InputIterator end) -> void;

        /// @brief Checks if a key is present in the Bloom filter.
        /// @param key_begin Pointer to the beginning of the key.
        /// @param length Length of the key.
        /// @return True if the key is present, false otherwise.
        [[nodiscard]] auto contains(const unsigned char* key_begin, std::size_t length) const -> bool;

        /// @brief Checks if a key is present in the Bloom filter.
        /// @tparam T Type of the key.
        /// @param t The key to check.
        /// @return True if the key is present, false otherwise.
        template <typename T>
        [[nodiscard]] auto contains(const T& t) const -> bool;

        /// @brief Checks if a string key is present in the Bloom filter.
        /// @param key The string key to check.
        /// @return True if the key is present, false otherwise.
        [[nodiscard]] auto contains(const std::string& key) const -> bool;

        /// @brief Checks if a key is present in the Bloom filter.
        /// @param data Pointer to the beginning of the key.
        /// @param length Length of the key.
        /// @return True if the key is present, false otherwise.
        [[nodiscard]] auto contains(const char* data, std::size_t length) const -> bool;

        /// @brief Checks if all keys in a range are present in the Bloom filter.
        /// @tparam InputIterator Type of the input iterator.
        /// @param begin Iterator to the beginning of the range.
        /// @param end Iterator to the end of the range.
        /// @return Iterator to the first key not found, or end if all are found.
        template <typename InputIterator>
        [[nodiscard]] auto contains_all(InputIterator begin, InputIterator end) const -> InputIterator;

        /// @brief Checks if none of the keys in a range are present in the Bloom filter.
        /// @tparam InputIterator Type of the input iterator.
        /// @param begin Iterator to the beginning of the range.
        /// @param end Iterator to the end of the range.
        /// @return Iterator to the first key found, or end if none are found.
        template <typename InputIterator>
        [[nodiscard]] auto contains_none(InputIterator begin, InputIterator end) const -> InputIterator;

        /// @brief Gets the size of the Bloom filter table in bits.
        /// @return The size of the table in bits.
        [[nodiscard]] auto size() const noexcept -> uint64_t;

        /// @brief Gets the number of elements inserted into the Bloom filter.
        /// @return The number of elements inserted.
        [[nodiscard]] auto element_count() const noexcept -> uint64_t;

        /// @brief Gets the effective false positive probability.
        /// @return The effective false positive probability.
        [[nodiscard]] auto effective_fpp() const noexcept -> double;

        /// @brief Gets a pointer to the Bloom filter table.
        /// @return A pointer to the table.
        [[nodiscard]] auto table() const noexcept -> const cell_type_*;

        /// @brief Gets the number of hash functions used.
        /// @return The number of hash functions.
        [[nodiscard]] auto hash_count() const noexcept -> std::size_t;

    private:
        /// @brief Computes the bit index and a bit of value from a hash value.
        /// @param hash The hash value to compute indices from.
        /// @param bit_index Reference to store the computed bit index.
        /// @param bit Reference to store the computed bit value.
        auto compute_indices(const bloom_type_& hash, std::size_t& bit_index, std::size_t& bit) const noexcept -> void;

        /// @brief Generates unique salt values for hash functions.
        auto generate_unique_salt() -> void;

        /// @brief Hash function using the AP (Arash Partow) algorithm.
        /// @param begin Pointer to the beginning of the data to hash.
        /// @param remaining_length Length of the data to hash.
        /// @param hash Initial hash value.
        /// @return The computed hash value.
        static auto hash_ap(const unsigned char* begin, std::size_t remaining_length, bloom_type_ hash) noexcept -> bloom_type_;

        std::vector<bloom_type_> salt_{};
        std::vector<unsigned char> bit_table_{};
        uint32_t salt_count_{};
        uint64_t table_size_{};
        uint64_t projected_element_count_{};
        uint64_t inserted_element_count_{};
        uint64_t random_seed_{};
        double desired_false_positive_probability_{};
    };

    [[nodiscard]] auto operator&(const BloomFilter& a, const BloomFilter& b) noexcept -> BloomFilter;
    [[nodiscard]] auto operator|(const BloomFilter& a, const BloomFilter& b) noexcept -> BloomFilter;
    [[nodiscard]] auto operator^(const BloomFilter& a, const BloomFilter& b) noexcept -> BloomFilter;
}
