#pragma once
#include <mutex>
#include <cstdint>

namespace fox
{
    /// @brief A class to generate unique IDs using the Snowflake algorithm.
    /// The Snowflake algorithm generates IDs that are roughly ordered by time,
    /// and consist of a timestamp, machine ID, datacenter ID, and a sequence number.
    /// This implementation ensures thread-safety through mutex locking.
    enum class SnowflakeOption : int64_t
    {
        machine_bits_ = 10,
        sequence_bits_ = 12,
        max_sequence_ = ~(-1LL << sequence_bits_),
        max_machine_id_ = ~(-1LL << 5),
        max_datacenter_id_ = ~(-1LL << 5),
    };

    /// @brief A utility class for generating unique IDs based on the Snowflake algorithm.
    /// The SnowflakeGenerator class produces 64-bit unique identifiers that combine:
    /// - A timestamp (42 bits)
    /// - A datacenter ID (5 bits)
    /// - A machine ID (5 bits)
    /// - A sequence number (12 bits)
    ///
    /// This implementation is thread-safe using a mutex to protect internal state during ID generation.
    /// Example usage:
    /// @code
    ///   fox::SnowflakeGenerator generator(1, 1);
    ///   int64_t id = generator.NextId();
    /// @endcode
    class SnowflakeGenerator
    {
    public:
        /// @brief Construct a SnowflakeGenerator with specified machine and datacenter IDs
        /// @param machine_id The machine ID (0-31)
        /// @param datacenter_id The datacenter ID (0-31)
        /// @throws std::invalid_argument If machine_id or datacenter_id is out of valid range
        SnowflakeGenerator(int16_t machine_id, int16_t datacenter_id);

        /// @brief Generate the next unique ID.
        /// @return The next unique ID.
        [[nodiscard]] auto NextId() -> int64_t;

    private:
        int64_t last_timestamp_{-1};
        int64_t sequence_{0};
        int16_t machine_id_{0};
        int16_t datacenter_id_{0};
        mutable std::mutex mutex_{};

        /// @brief Get current timestamp in milliseconds.
        /// @return Current timestamp.
        [[nodiscard]] static auto GetCurrentTimestamp() noexcept -> int64_t;

        /// @brief Wait until next millisecond when sequence number overflows.
        /// @param last_timestamp The last timestamp.
        /// @return The next valid timestamp.
        [[nodiscard]] static auto TilNextMillis(int64_t last_timestamp) noexcept -> int64_t;
    };
}
