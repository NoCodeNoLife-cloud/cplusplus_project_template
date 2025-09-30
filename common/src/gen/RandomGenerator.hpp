#pragma once

#include <random>
#include <string>
#include <stdexcept>
#include <mutex>

namespace fox
{
    class RandomGenerator
    {
    public:
        /// @brief Default constructor: initializes seed using random device
        RandomGenerator() noexcept;

        /// @brief Constructor with specified seed
        /// @param seed The seed value for the random number generator
        explicit RandomGenerator(unsigned int seed) noexcept;

        /// @brief Generates a random integer in the range [min, max]
        /// @param min The minimum value (inclusive)
        /// @param max The maximum value (inclusive)
        /// @return A random integer in the specified range
        /// @throws std::invalid_argument if min > max
        auto nextInt(int min, int max) -> int;

        /// @brief Generates a random boolean with 50% probability
        /// @return A random boolean value
        auto nextBool() -> bool;

        /// @brief Generates a random boolean with specified probability
        /// @param trueProbability Probability of returning true (must be between 0.0 and 1.0)
        /// @return A random boolean value
        /// @throws std::invalid_argument if trueProbability is not in [0, 1]
        auto nextBool(double trueProbability) -> bool;

        /// @brief Generates a random floating-point number in the range [min, max)
        /// @param min The minimum value (inclusive)
        /// @param max The maximum value (exclusive)
        /// @return A random double in the specified range
        /// @throws std::invalid_argument if min >= max
        auto nextDouble(double min, double max) -> double;

        /// @brief Generates a random string of specified length
        /// @param length The length of the string to generate
        /// @param charset The character set to use for generation
        /// @return A random string of specified length
        /// @throws std::invalid_argument if charset is empty
        auto nextString(size_t length, const std::string& charset =
                            "abcdefghijklmnopqrstuvwxyz"
                            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                            "0123456789") -> std::string;

        /// @brief Generates a Gaussian distributed random number
        /// @param mean The mean of the distribution
        /// @param stddev The standard deviation of the distribution (must be positive)
        /// @return A Gaussian distributed random number
        /// @throws std::invalid_argument if stddev is not positive
        auto nextGaussian(double mean = 0.0, double stddev = 1.0) -> double;

        /// @brief Thread-safe: sets a new seed
        /// @param seed The new seed value
        auto setSeed(unsigned int seed) -> void;

    private:
        std::mt19937 engine_; ///< Mersenne Twister random number engine
        std::mutex mutex_; ///< Mutex for thread safety
    };

    inline RandomGenerator::RandomGenerator() noexcept : engine_(std::random_device{}())
    {
    }

    inline RandomGenerator::RandomGenerator(const unsigned int seed) noexcept : engine_(seed)
    {
    }

    inline auto RandomGenerator::nextInt(const int min, const int max) -> int
    {
        if (min > max)
        {
            throw std::invalid_argument("nextInt: min cannot be greater than max");
        }
        std::lock_guard<std::mutex> lock(mutex_);
        std::uniform_int_distribution<int> dist(min, max);
        return dist(engine_);
    }

    inline auto RandomGenerator::nextBool() -> bool
    {
        return nextBool(0.5);
    }

    inline auto RandomGenerator::nextBool(const double trueProbability) -> bool
    {
        if (trueProbability < 0.0 || trueProbability > 1.0)
        {
            throw std::invalid_argument("nextBool: probability must be in [0, 1]");
        }
        std::lock_guard<std::mutex> lock(mutex_);
        std::bernoulli_distribution dist(trueProbability);
        return dist(engine_);
    }

    inline auto RandomGenerator::nextDouble(const double min, const double max) -> double
    {
        if (min >= max)
        {
            throw std::invalid_argument("nextDouble: min must be less than max");
        }
        std::lock_guard<std::mutex> lock(mutex_);
        std::uniform_real_distribution<double> dist(min, max);
        return dist(engine_);
    }

    inline auto RandomGenerator::nextString(const size_t length, const std::string& charset) -> std::string
    {
        if (charset.empty())
        {
            throw std::invalid_argument("nextString: charset cannot be empty");
        }
        if (length == 0)
        {
            return {};
        }

        std::lock_guard<std::mutex> lock(mutex_);
        std::string result;
        result.reserve(length);

        // Pre-calculate charset size to avoid repeated size() calls
        const size_t charSetSize = charset.size();
        std::uniform_int_distribution<size_t> dist(0, charSetSize - 1);

        for (size_t i = 0; i < length; ++i)
        {
            result += charset[dist(engine_)];
        }
        return result;
    }

    inline auto RandomGenerator::nextGaussian(const double mean, const double stddev) -> double
    {
        if (stddev <= 0.0)
        {
            throw std::invalid_argument("nextGaussian: stddev must be positive");
        }
        std::lock_guard<std::mutex> lock(mutex_);
        std::normal_distribution<double> dist(mean, stddev);
        return dist(engine_);
    }

    inline auto RandomGenerator::setSeed(const unsigned int seed) -> void
    {
        std::lock_guard<std::mutex> lock(mutex_);
        engine_.seed(seed);
    }
}
