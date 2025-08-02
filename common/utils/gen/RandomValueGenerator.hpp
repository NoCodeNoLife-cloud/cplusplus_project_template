#pragma once
#include <random>
#include <type_traits>

namespace common {
template <typename T>
concept ValidType = std::is_integral_v<T> || std::is_floating_point_v<T>;

template <ValidType T>
class RandomValueGenerator {
 public:
  RandomValueGenerator();
  explicit RandomValueGenerator(const std::mt19937::result_type& seed);
  T generate(T min, T max);

 private:
  std::mt19937 engine_;
};

template <ValidType T>
RandomValueGenerator<T>::RandomValueGenerator() {
  std::random_device rd;
  std::seed_seq seed_seq{rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()};
  engine_.seed(seed_seq);
}

template <ValidType T>
RandomValueGenerator<T>::RandomValueGenerator(const std::mt19937::result_type& seed) : engine_(seed) {}

template <ValidType T>
T RandomValueGenerator<T>::generate(T min, T max) {
  if (min > max) {
    std::swap(min, max);
  }

  if constexpr (std::is_floating_point_v<T>) {
    std::uniform_real_distribution<T> dist(min, max);
    return dist(engine_);
  } else {
    std::uniform_int_distribution<T> dist(min, max);
    return dist(engine_);
  }
}
}  // namespace common
