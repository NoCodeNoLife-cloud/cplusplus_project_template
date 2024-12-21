#pragma once
#include <random>

namespace common::gen
{
    class RandomGenerator abstract
    {
    public:
        RandomGenerator();
        explicit RandomGenerator(int64_t seed);
        auto nextBoolean() -> bool;
        auto nextBytes(std::vector<unsigned char>& bytes) -> void;
        auto nextDouble() -> double;
        auto nextFloat() -> float;
        auto nextGaussian() -> double;
        auto nextInt() -> int32_t;
        auto nextInt(int32_t n) -> int32_t;
        auto nextLong() -> int64_t;
        auto setSeed(int64_t seed) -> void;
    protected:
        std::mt19937 generator;
        std::uniform_real_distribution<> realDist;
        std::normal_distribution<> normalDist;
        int32_t next(int32_t bits);
    };
}
