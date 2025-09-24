#pragma once
#include <chrono>
#include <mutex>
#include <stdexcept>
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
        SnowflakeGenerator(int16_t machine_id, int16_t datacenter_id);

        /// @brief Generate the next unique ID.
        /// @return The next unique ID.
        [[nodiscard]] auto NextId() -> int64_t;

    private:
        int64_t last_timestamp_{-1};
        int64_t sequence_{0};
        int16_t machine_id_;
        mutable std::mutex mutex_;

        /// @brief Get current timestamp in milliseconds.
        /// @return Current timestamp.
        [[nodiscard]] static auto GetCurrentTimestamp() noexcept -> int64_t;

        /// @brief Wait until next millisecond when sequence number overflows.
        /// @param last_timestamp The last timestamp.
        /// @return The next valid timestamp.
        [[nodiscard]] static auto TilNextMillis(int64_t last_timestamp) noexcept -> int64_t;
    };

    inline SnowflakeGenerator::SnowflakeGenerator(const int16_t machine_id, const int16_t datacenter_id)
    {
        if (machine_id < 0 || machine_id > static_cast<int64_t>(SnowflakeOption::max_machine_id_))
        {
            throw std::invalid_argument("Machine ID out of range (0-31)");
        }
        if (datacenter_id < 0 || datacenter_id > static_cast<int64_t>(SnowflakeOption::max_datacenter_id_))
        {
            throw std::invalid_argument("Datacenter ID out of range (0-31)");
        }
        machine_id_ = static_cast<int16_t>(datacenter_id << 5 | machine_id);
    }

    inline auto SnowflakeGenerator::NextId() -> int64_t
    {
        std::lock_guard<std::mutex> lock(mutex_);
        int64_t timestamp = GetCurrentTimestamp();

        if (timestamp < last_timestamp_)
        {
            do
            {
                timestamp = GetCurrentTimestamp();
            }
            while (timestamp < last_timestamp_);
        }

        if (timestamp == last_timestamp_)
        {
            sequence_ = (sequence_ + 1) & static_cast<int64_t>(SnowflakeOption::max_sequence_);
            if (sequence_ == 0)
            {
                timestamp = TilNextMillis(last_timestamp_);
            }
        }
        else
        {
            sequence_ = 0;
        }

        last_timestamp_ = timestamp;

        return (timestamp << (static_cast<int64_t>(SnowflakeOption::machine_bits_) +
                static_cast<int64_t>(SnowflakeOption::sequence_bits_))) |
            (static_cast<int64_t>(machine_id_) << static_cast<int64_t>(SnowflakeOption::sequence_bits_)) | sequence_;
    }

    inline auto SnowflakeGenerator::GetCurrentTimestamp() noexcept -> int64_t
    {
        const auto now = std::chrono::system_clock::now();
        const auto duration = now.time_since_epoch();
        const int64_t timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        constexpr int64_t start_time = 1288855200000LL;
        return timestamp - start_time;
    }

    inline auto SnowflakeGenerator::TilNextMillis(const int64_t last_timestamp) noexcept -> int64_t
    {
        int64_t timestamp = GetCurrentTimestamp();
        while (timestamp <= last_timestamp)
        {
            timestamp = GetCurrentTimestamp();
        }
        return timestamp;
    }
}
