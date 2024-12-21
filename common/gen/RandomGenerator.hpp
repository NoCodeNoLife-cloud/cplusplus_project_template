#pragma once
#include <random>

namespace common::gen
{
    class RandomGenerator abstract
    {
    public:
        RandomGenerator();
        explicit RandomGenerator(long seed);
        auto nextBoolean() -> bool;
        auto nextBytes(std::vector<unsigned char>& bytes) -> void;
        auto nextDouble() -> double;
        auto nextFloat() -> float;
        auto nextGaussian() -> double;
        auto nextInt() -> int;
        auto nextInt(int n) -> int;
        auto nextLong() -> long;
        auto setSeed(long seed) -> void;

    protected:
        std::mt19937 generator;
        std::uniform_real_distribution<> realDist;
        std::normal_distribution<> normalDist;
        int next(int bits);
    };

    inline RandomGenerator::RandomGenerator(): generator(std::random_device{}()), realDist(0.0, 1.0),
                                               normalDist(0.0, 1.0)
    {
    }

    inline RandomGenerator::RandomGenerator(const long seed): generator(seed), realDist(0.0, 1.0), normalDist(0.0, 1.0)
    {
    }

    inline bool RandomGenerator::nextBoolean()
    {
        std::bernoulli_distribution dist(0.5);
        return dist(generator);
    }

    inline auto RandomGenerator::nextBytes(std::vector<unsigned char>& bytes) -> void
    {
        std::uniform_int_distribution<unsigned int> dist(0, 255);
        std::generate(bytes.begin(), bytes.end(), [&]()
        {
            return static_cast<unsigned char>(dist(generator));
        });
    }

    inline auto RandomGenerator::nextDouble() -> double
    {
        return realDist(generator);
    }

    inline auto RandomGenerator::nextFloat() -> float
    {
        return static_cast<float>(realDist(generator));
    }

    inline auto RandomGenerator::nextGaussian() -> double
    {
        return normalDist(generator);
    }

    inline auto RandomGenerator::nextInt() -> int
    {
        return next(32);
    }

    inline auto RandomGenerator::nextInt(int n) -> int
    {
        if (n <= 0)
        {
            throw std::invalid_argument("n must be greater than 0");
        }
        std::uniform_int_distribution<int> dist(0, n - 1);
        return dist(generator);
    }

    inline auto RandomGenerator::nextLong() -> long
    {
        std::uniform_int_distribution<long> dist(0, LONG_MAX);
        return dist(generator);
    }

    inline auto RandomGenerator::setSeed(long seed) -> void
    {
        generator.seed(seed);
    }

    inline auto RandomGenerator::next(int bits) -> int
    {
        std::uniform_int_distribution<int> dist(0, (1 << bits) - 1);
        return dist(generator);
    }
}
