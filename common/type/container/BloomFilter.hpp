#pragma once
#include <iterator>
#include <random>
#include <string>
#include <vector>
#include <algorithm>

#include "BloomParameters.hpp"

namespace fox
{
    static const unsigned char bit_mask[BITS_PER_CHAR] = {
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
    /// @tparam bloom_type_ The type used for hash values (uint32_t)
    /// @tparam cell_type_ The type used for bit array cells (unsigned char)
    /// @tparam table_type_ The type used for the bit array (std::vector<unsigned char>)
    class BloomFilter final
    {
    protected:
        using bloom_type_ = uint32_t;
        using cell_type_ = unsigned char;
        using table_type_ = std::vector<unsigned char>;

    public:
        BloomFilter();

        explicit BloomFilter(const BloomParameters& p) noexcept;

        BloomFilter(const BloomFilter& filter);

        ~BloomFilter();

        /// @brief Compares two Bloom filters for equality.
        /// @param f The Bloom filter to compare with.
        /// @return True if the filters are equal, false otherwise.
        auto operator==(const BloomFilter& f) const noexcept -> bool;

        /// @brief Compares two Bloom filters for inequality.
        /// @param f The Bloom filter to compare with.
        /// @return True if the filters are not equal, false otherwise.
        auto operator!=(const BloomFilter& f) const noexcept -> bool;

        /// @brief Assigns one Bloom filter to another.
        /// @param f The Bloom filter to assign from.
        /// @return A reference to the assigned Bloom filter.
        auto operator=(const BloomFilter& f) -> BloomFilter&;

        /// @brief Checks if the Bloom filter is empty.
        /// @return True if the filter is empty, false otherwise.
        auto operator!() const noexcept -> bool;

        /// @brief Clears all elements from the Bloom filter.
        auto clear() noexcept -> void;

        /// @brief Inserts a key into the Bloom filter.
        /// @param key_begin Pointer to the beginning of the key.
        /// @param length Length of the key.
        auto insert(const unsigned char* key_begin, const std::size_t& length) -> void;

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
        auto insert(const char* data, const std::size_t& length) -> void;

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
        auto contains(const unsigned char* key_begin, std::size_t length) const -> bool;

        /// @brief Checks if a key is present in the Bloom filter.
        /// @tparam T Type of the key.
        /// @param t The key to check.
        /// @return True if the key is present, false otherwise.
        template <typename T>
        auto contains(const T& t) const -> bool;

        /// @brief Checks if a string key is present in the Bloom filter.
        /// @param key The string key to check.
        /// @return True if the key is present, false otherwise.
        [[nodiscard]] auto contains(const std::string& key) const -> bool;

        /// @brief Checks if a key is present in the Bloom filter.
        /// @param data Pointer to the beginning of the key.
        /// @param length Length of the key.
        /// @return True if the key is present, false otherwise.
        auto contains(const char* data, const std::size_t& length) const -> bool;

        /// @brief Checks if all keys in a range are present in the Bloom filter.
        /// @tparam InputIterator Type of the input iterator.
        /// @param begin Iterator to the beginning of the range.
        /// @param end Iterator to the end of the range.
        /// @return Iterator to the first key not found, or end if all are found.
        template <typename InputIterator>
        auto contains_all(InputIterator begin, InputIterator end) const -> InputIterator;

        /// @brief Checks if none of the keys in a range are present in the Bloom filter.
        /// @tparam InputIterator Type of the input iterator.
        /// @param begin Iterator to the beginning of the range.
        /// @param end Iterator to the end of the range.
        /// @return Iterator to the first key found, or end if none are found.
        template <typename InputIterator>
        auto contains_none(InputIterator begin, InputIterator end) const -> InputIterator;

        /// @brief Gets the size of the Bloom filter table in bits.
        /// @return The size of the table in bits.
        [[nodiscard]] auto size() const noexcept -> uint64_t;

        /// @brief Gets the number of elements inserted into the Bloom filter.
        /// @return The number of elements inserted.
        [[nodiscard]] auto element_count() const noexcept -> uint64_t;

        /// @brief Gets the effective false positive probability.
        /// @return The effective false positive probability.
        [[nodiscard]] auto effective_fpp() const noexcept -> double;

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

        /// @brief Gets a pointer to the Bloom filter table.
        /// @return A pointer to the table.
        [[nodiscard]] auto table() const noexcept -> const cell_type_*;

        /// @brief Gets the number of hash functions used.
        /// @return The number of hash functions.
        [[nodiscard]] auto hash_count() const noexcept -> std::size_t;

    protected:
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
        static auto hash_ap(const unsigned char* begin, std::size_t remaining_length,
                            bloom_type_ hash) noexcept -> bloom_type_;

        std::vector<bloom_type_> salt_;
        std::vector<unsigned char> bit_table_;
        uint32_t salt_count_{};
        uint64_t table_size_{};
        uint64_t projected_element_count_{};
        uint64_t inserted_element_count_{};
        uint64_t random_seed_{};
        double desired_false_positive_probability_{};
    };

    inline BloomFilter::BloomFilter() = default;

    inline BloomFilter::BloomFilter(const BloomParameters& p) noexcept :
        projected_element_count_(p.projected_element_count), random_seed_(p.random_seed * 0xA5A5A5A5 + 1),
        desired_false_positive_probability_(p.false_positive_probability)
    {
        salt_count_ = p.optimal_parameters.number_of_hashes;
        table_size_ = p.optimal_parameters.table_size;

        generate_unique_salt();

        bit_table_.resize(table_size_ / BITS_PER_CHAR, 0x00);
    }

    inline BloomFilter::BloomFilter(const BloomFilter& filter)
    {
        this->operator=(filter);
    }

    inline BloomFilter::~BloomFilter() = default;

    inline auto BloomFilter::operator==(const BloomFilter& f) const noexcept -> bool
    {
        if (this != &f)
        {
            return salt_count_ == f.salt_count_ && table_size_ == f.table_size_ &&
                bit_table_.size() == f.bit_table_.size() && projected_element_count_ == f.projected_element_count_
                &&
                inserted_element_count_ == f.inserted_element_count_ && random_seed_ == f.random_seed_ &&
                desired_false_positive_probability_ == f.desired_false_positive_probability_ && salt_ == f.salt_ &&
                bit_table_ == f.bit_table_;
        }
        return true;
    }

    inline auto BloomFilter::operator!=(const BloomFilter& f) const noexcept -> bool
    {
        return !operator==(f);
    }

    inline auto BloomFilter::operator=(const BloomFilter& f) -> BloomFilter&
    {
        if (this != &f)
        {
            salt_count_ = f.salt_count_;
            table_size_ = f.table_size_;
            bit_table_ = f.bit_table_;
            salt_ = f.salt_;

            projected_element_count_ = f.projected_element_count_;
            inserted_element_count_ = f.inserted_element_count_;

            random_seed_ = f.random_seed_;

            desired_false_positive_probability_ = f.desired_false_positive_probability_;
        }

        return *this;
    }

    inline auto BloomFilter::operator!() const noexcept -> bool
    {
        return 0 == table_size_;
    }

    inline auto BloomFilter::clear() noexcept -> void
    {
        std::ranges::fill(bit_table_, static_cast<unsigned char>(0x00));
        inserted_element_count_ = 0;
    }

    inline auto BloomFilter::insert(const unsigned char* key_begin, const std::size_t& length) -> void
    {
        std::size_t bit_index = 0;
        std::size_t bit = 0;

        for (const uint32_t i : salt_)
        {
            compute_indices(hash_ap(key_begin, length, i), bit_index, bit);

            bit_table_[bit_index / BITS_PER_CHAR] |= bit_mask[bit];
        }

        ++inserted_element_count_;
    }

    template <typename T>
    auto BloomFilter::insert(const T& t) -> void
    {
        insert(reinterpret_cast<const unsigned char*>(&t), sizeof(T));
    }

    inline auto BloomFilter::insert(const std::string& key) -> void
    {
        insert(reinterpret_cast<const unsigned char*>(key.data()), key.size());
    }

    inline auto BloomFilter::insert(const char* data, const std::size_t& length) -> void
    {
        insert(reinterpret_cast<const unsigned char*>(data), length);
    }

    template <typename InputIterator>
    auto BloomFilter::insert(InputIterator begin, InputIterator end) -> void
    {
        InputIterator itr = begin;

        while (end != itr)
        {
            insert(*itr++);
        }
    }

    inline auto BloomFilter::contains(const unsigned char* key_begin, const std::size_t length) const -> bool
    {
        std::size_t bit_index = 0;
        std::size_t bit = 0;

        for (const uint32_t i : salt_)
        {
            compute_indices(hash_ap(key_begin, length, i), bit_index, bit);

            if ((bit_table_[bit_index / BITS_PER_CHAR] & bit_mask[bit]) != bit_mask[bit])
            {
                return false;
            }
        }

        return true;
    }

    template <typename T>
    auto BloomFilter::contains(const T& t) const -> bool
    {
        return contains(reinterpret_cast<const unsigned char*>(&t), sizeof(T));
    }

    inline auto BloomFilter::contains(const std::string& key) const -> bool
    {
        return contains(reinterpret_cast<const unsigned char*>(key.c_str()), key.size());
    }

    inline auto BloomFilter::contains(const char* data, const std::size_t& length) const -> bool
    {
        return contains(reinterpret_cast<const unsigned char*>(data), length);
    }

    template <typename InputIterator>
    auto BloomFilter::contains_all(InputIterator begin, InputIterator end) const -> InputIterator
    {
        InputIterator itr = begin;

        while (end != itr)
        {
            if (!contains(*itr))
            {
                return itr;
            }

            ++itr;
        }

        return end;
    }

    template <typename InputIterator>
    auto BloomFilter::contains_none(InputIterator begin, InputIterator end) const -> InputIterator
    {
        InputIterator itr = begin;

        while (end != itr)
        {
            if (contains(*itr))
            {
                return itr;
            }

            ++itr;
        }

        return end;
    }

    inline auto BloomFilter::size() const noexcept -> uint64_t
    {
        return table_size_;
    }

    inline auto BloomFilter::element_count() const noexcept -> uint64_t
    {
        return inserted_element_count_;
    }

    inline auto BloomFilter::effective_fpp() const noexcept -> double
    {
        return std::pow(1.0 - std::exp(-1.0 * static_cast<double>(salt_.size()) *
                            static_cast<double>(inserted_element_count_) / static_cast<double>(size())),
                        1.0 * static_cast<double>(salt_.size()));
    }

    inline auto BloomFilter::operator&=(const BloomFilter& f) -> BloomFilter&
    {
        /* intersection */
        if (salt_count_ == f.salt_count_ && table_size_ == f.table_size_ && random_seed_ == f.random_seed_)
        {
            for (std::size_t i = 0; i < bit_table_.size(); ++i)
            {
                bit_table_[i] &= f.bit_table_[i];
            }
        }

        return *this;
    }

    inline auto BloomFilter::operator|=(const BloomFilter& f) -> BloomFilter&
    {
        /* union */
        if (salt_count_ == f.salt_count_ && table_size_ == f.table_size_ && random_seed_ == f.random_seed_)
        {
            for (std::size_t i = 0; i < bit_table_.size(); ++i)
            {
                bit_table_[i] |= f.bit_table_[i];
            }
        }

        return *this;
    }

    inline auto BloomFilter::operator^=(const BloomFilter& f) -> BloomFilter&
    {
        /* difference */
        if (salt_count_ == f.salt_count_ && table_size_ == f.table_size_ && random_seed_ == f.random_seed_)
        {
            for (std::size_t i = 0; i < bit_table_.size(); ++i)
            {
                bit_table_[i] ^= f.bit_table_[i];
            }
        }

        return *this;
    }

    inline auto BloomFilter::table() const noexcept -> const cell_type_*
    {
        return bit_table_.data();
    }

    inline auto BloomFilter::hash_count() const noexcept -> std::size_t
    {
        return salt_.size();
    }

    inline auto BloomFilter::compute_indices(const bloom_type_& hash, std::size_t& bit_index,
                                             std::size_t& bit) const noexcept -> void
    {
        bit_index = hash % table_size_;
        bit = bit_index % BITS_PER_CHAR;
    }

    inline auto BloomFilter::generate_unique_salt() -> void
    {
        constexpr uint32_t pre_def_salt_count = 128;

        static constexpr bloom_type_ pre_def_salt[pre_def_salt_count] = {
            0xAAAAAAAA, 0x55555555, 0x33333333, 0xCCCCCCCC, 0x66666666, 0x99999999, 0xB5B5B5B5, 0x4B4B4B4B,
            0xAA55AA55,
            0x55335533, 0x33CC33CC, 0xCC66CC66, 0x66996699, 0x99B599B5, 0xB54BB54B, 0x4BAA4BAA, 0xAA33AA33,
            0x55CC55CC,
            0x33663366, 0xCC99CC99, 0x66B566B5, 0x994B994B, 0xB5AAB5AA, 0xAAAAAA33, 0x555555CC, 0x33333366,
            0xCCCCCC99,
            0x666666B5, 0x9999994B, 0xB5B5B5AA, 0xFFFFFFFF, 0xFFFF0000, 0xB823D5EB, 0xC1191CDF, 0xF623AEB3,
            0xDB58499F,
            0xC8D42E70, 0xB173F616, 0xA91A5967, 0xDA427D63, 0xB1E8A2EA, 0xF6C0D155, 0x4909FEA3, 0xA68CC6A7,
            0xC395E782,
            0xA26057EB, 0x0CD5DA28, 0x467C5492, 0xF15E6982, 0x61C6FAD3, 0x9615E352, 0x6E9E355A, 0x689B563E,
            0x0C9831A8,
            0x6753C18B, 0xA622689B, 0x8CA63C47, 0x42CC2884, 0x8E89919B, 0x6EDBD7D3, 0x15B6796C, 0x1D6FDFE4,
            0x63FF9092,
            0xE7401432, 0xEFFE9412, 0xAEAEDF79, 0x9F245A31, 0x83C136FC, 0xC3DA4A8C, 0xA5112C8C, 0x5271F491,
            0x9A948DAB,
            0xCEE59A8D, 0xB5F525AB, 0x59D13217, 0x24E7C331, 0x697C2103, 0x84B0A460, 0x86156DA9, 0xAEF2AC68,
            0x23243DA5,
            0x3F649643, 0x5FA495A8, 0x67710DF8, 0x9A6C499E, 0xDCFB0227, 0x46A43433, 0x1832B07A, 0xC46AFF3C,
            0xB9C8FFF0,
            0xC9500467, 0x34431BDF, 0xB652432B, 0xE367F12B, 0x427F4C1B, 0x224C006E, 0x2E7E5A89, 0x96F99AA5,
            0x0BEB452A,
            0x2FD87C39, 0x74B2E1FB, 0x222EFD24, 0xF357F60C, 0x440FCB1E, 0x8BBE030F, 0x6704DC29, 0x1144D12F,
            0x948B1355,
            0x6D8FD7E9, 0x1C11A014, 0xADD1592F, 0xFB3C712E, 0xFC77642F, 0xF9C4CE8C, 0x31312FB9, 0x08B0DD79,
            0x318FA6E7,
            0xC040D23D, 0xC0589AA7, 0x0CA5C075, 0xF874B172, 0x0CF914D5, 0x784D3280, 0x4E8CFEBC, 0xC569F575,
            0xCDB2A091,
            0x2CC016B4, 0x5C5F4421
        };

        if (salt_count_ <= pre_def_salt_count)
        {
            std::copy_n(pre_def_salt, salt_count_, std::back_inserter(salt_));
            for (std::size_t i = 0; i < salt_.size(); ++i)
            {
                salt_[i] = salt_[i] * salt_[(i + 3) % salt_.size()] + static_cast<bloom_type_>(random_seed_);
            }
        }
        else
        {
            std::copy_n(pre_def_salt, pre_def_salt_count, std::back_inserter(salt_));
            // srand(static_cast<uint32_t>(random_seed_));
            std::mt19937 gen(static_cast<uint32_t>(random_seed_));
            std::uniform_int_distribution<bloom_type_> distribution;
            while (salt_.size() < salt_count_)
            {
                bloom_type_ current_salt = distribution(gen) * distribution(gen);

                if (0 == current_salt)
                    continue;

                if (salt_.end() == std::ranges::find(salt_, current_salt))
                {
                    salt_.push_back(current_salt);
                }
            }
        }
    }

    inline auto BloomFilter::hash_ap(const unsigned char* begin, std::size_t remaining_length,
                                     bloom_type_ hash) noexcept -> bloom_type_
    {
        const unsigned char* itr = begin;

        while (remaining_length >= 8)
        {
            const uint32_t& i1 = *reinterpret_cast<const uint32_t*>(itr);
            itr += sizeof(uint32_t);
            const uint32_t& i2 = *reinterpret_cast<const uint32_t*>(itr);
            itr += sizeof(uint32_t);

            hash ^= hash << 7 ^ i1 * (hash >> 3) ^ ~((hash << 11) + (i2 ^ hash >> 5));

            remaining_length -= 8;
        }

        if (remaining_length)
        {
            uint32_t loop = 0;
            if (remaining_length >= 4)
            {
                const uint32_t& i = *reinterpret_cast<const uint32_t*>(itr);

                if (loop & 0x01)
                {
                    hash ^= hash << 7 ^ i * (hash >> 3);
                }
                else
                {
                    hash ^= ~((hash << 11) + (i ^ hash >> 5));
                }

                ++loop;
                remaining_length -= 4;
                itr += sizeof(uint32_t);
            }

            if (remaining_length >= 2)
            {
                const uint16_t& i = *reinterpret_cast<const uint16_t*>(itr);

                if (loop & 0x01)
                {
                    hash ^= hash << 7 ^ i * (hash >> 3);
                }
                else
                {
                    hash ^= ~((hash << 11) + (i ^ hash >> 5));
                }

                ++loop;
                remaining_length -= 2;
                itr += sizeof(uint16_t);
            }

            if (remaining_length)
            {
                hash += (*itr ^ hash * 0xA5A5A5A5) + loop;
            }
        }

        return hash;
    }

    inline auto operator&(const BloomFilter& a, const BloomFilter& b) noexcept -> BloomFilter
    {
        BloomFilter result = a;
        result &= b;
        return result;
    }

    inline auto operator|(const BloomFilter& a, const BloomFilter& b) noexcept -> BloomFilter
    {
        BloomFilter result = a;
        result |= b;
        return result;
    }

    inline auto operator^(const BloomFilter& a, const BloomFilter& b) noexcept -> BloomFilter
    {
        BloomFilter result = a;
        result ^= b;
        return result;
    }
}
