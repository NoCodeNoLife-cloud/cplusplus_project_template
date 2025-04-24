#include "RandomGenerator.hpp"

namespace framework::gen {
  RandomGenerator::RandomGenerator() : generator(std::random_device{}()), real_dist_(0.0, 1.0), normal_dist_(0.0, 1.0) {}

  RandomGenerator::RandomGenerator(const int64_t seed) : generator(seed), real_dist_(0.0, 1.0), normal_dist_(0.0, 1.0) {}

  bool RandomGenerator::nextBoolean() {
    std::bernoulli_distribution dist(0.5);
    return dist(generator);
  }

  auto RandomGenerator::nextBytes(std::vector<unsigned char>& bytes) -> void {
    std::uniform_int_distribution<uint32_t> dist(0, 255);
    std::ranges::generate(bytes, [&]
    {
      return static_cast<unsigned char>(dist(generator));
    });
  }

  auto RandomGenerator::nextDouble() -> double {
    return real_dist_(generator);
  }

  auto RandomGenerator::nextFloat() -> float {
    return static_cast<float>(real_dist_(generator));
  }

  auto RandomGenerator::nextGaussian() -> double {
    return normal_dist_(generator);
  }

  auto RandomGenerator::nextInt() -> int32_t {
    return next_(32);
  }

  auto RandomGenerator::nextInt(const int32_t n) -> int32_t {
    if (n <= 0) {
      throw std::invalid_argument("n must be greater than 0");
    }
    std::uniform_int_distribution dist(0, n - 1);
    return dist(generator);
  }

  auto RandomGenerator::nextLong() -> int64_t {
    std::uniform_int_distribution<int64_t> dist(0, LONG_MAX);
    return dist(generator);
  }

  auto RandomGenerator::setSeed(const int64_t seed) -> void {
    generator.seed(seed);
  }

  auto RandomGenerator::next_(const int32_t bits) -> int32_t {
    std::uniform_int_distribution dist(0, (1 << bits) - 1);
    return dist(generator);
  }
} // namespace framework::gen
