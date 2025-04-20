#pragma once
#include <random>

namespace framework::gen {
  class RandomGenerator {
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
    std::uniform_real_distribution<> real_dist_;
    std::normal_distribution<> normal_dist_;

    int32_t next_(int32_t bits);
  };
} // namespace framework::gen
