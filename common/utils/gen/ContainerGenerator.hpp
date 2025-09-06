#pragma once
#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <random>
#include <set>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace fox {
/// @brief A utility class for generating various STL containers with random values.
/// This class provides static methods to generate vectors, dequeue, lists, forward lists,
/// arrays, sets, multiset, unordered sets, unordered multiset, maps, multimaps,
/// unordered maps, and unordered multimaps populated with random data within specified ranges.
class ContainerGenerator {
 public:
  /// @brief Generate a vector with random values within the specified range.
  /// @tparam T The type of the elements.
  /// @param minValue The minimum value (inclusive).
  /// @param maxValue The maximum value (inclusive).
  /// @param size The number of elements to generate.
  /// @return A vector containing the generated values.
  template <typename T>
  static auto generateVector(T minValue, T maxValue, int32_t size) -> std::vector<T>;

  /// @brief Generate a deque with random values within the specified range.
  /// @tparam T The type of the elements.
  /// @param minValue The minimum value (inclusive).
  /// @param maxValue The maximum value (inclusive).
  /// @param size The number of elements to generate.
  /// @return A deque containing the generated values.
  template <typename T>
  static auto generateDeque(T minValue, T maxValue, int32_t size) -> std::deque<T>;

  /// @brief Generate a list with random values within the specified range.
  /// @tparam T The type of the elements.
  /// @param minValue The minimum value (inclusive).
  /// @param maxValue The maximum value (inclusive).
  /// @param size The number of elements to generate.
  /// @return A list containing the generated values.
  template <typename T>
  static auto generateList(T minValue, T maxValue, int32_t size) -> std::list<T>;

  /// @brief Generate a forward list with random values within the specified range.
  /// @tparam T The type of the elements.
  /// @param minValue The minimum value (inclusive).
  /// @param maxValue The maximum value (inclusive).
  /// @param size The number of elements to generate.
  /// @return A forward list containing the generated values.
  template <typename T>
  static auto generateForwardList(T minValue, T maxValue, int32_t size) -> std::forward_list<T>;

  /// @brief Generate an array with random values within the specified range.
  /// @tparam T The type of the elements.
  /// @tparam N The size of the array.
  /// @param minValue The minimum value (inclusive).
  /// @param maxValue The maximum value (inclusive).
  /// @return An array containing the generated values.
  template <typename T, size_t N>
  static auto generateArray(T minValue, T maxValue) -> std::array<T, N>;

  /// @brief Generate a set with random values within the specified range.
  /// @tparam T The type of the elements.
  /// @param minValue The minimum value (inclusive).
  /// @param maxValue The maximum value (inclusive).
  /// @param size The number of elements to generate.
  /// @return A set containing the generated values.
  template <typename T>
  static auto generateSet(T minValue, T maxValue, int32_t size) -> std::set<T>;

  /// @brief Generate an unordered set with random values within the specified range.
  /// @tparam T The type of the elements.
  /// @param minValue The minimum value (inclusive).
  /// @param maxValue The maximum value (inclusive).
  /// @param size The number of elements to generate.
  /// @return An unordered set containing the generated values.
  template <typename T>
  static auto generateUnorderedSet(T minValue, T maxValue, int32_t size) -> std::unordered_set<T>;

  /// @brief Generate a multiset with random values within the specified range.
  /// @tparam T The type of the elements.
  /// @param minValue The minimum value (inclusive).
  /// @param maxValue The maximum value (inclusive).
  /// @param size The number of elements to generate.
  /// @return A multiset containing the generated values.
  template <typename T>
  static auto generateMultiSet(T minValue, T maxValue, int32_t size) -> std::multiset<T>;

  /// @brief Generate an unordered multiset with random values within the specified range.
  /// @tparam T The type of the elements.
  /// @param minValue The minimum value (inclusive).
  /// @param maxValue The maximum value (inclusive).
  /// @param size The number of elements to generate.
  /// @return An unordered multiset containing the generated values.
  template <typename T>
  static auto generateUnorderedMultiSet(T minValue, T maxValue, int32_t size) -> std::unordered_multiset<T>;

  /// @brief Generate a map with random key-value pairs within the specified ranges.
  /// @tparam T The type of the keys.
  /// @tparam U The type of the values.
  /// @param minKey The minimum key value (inclusive).
  /// @param maxKey The maximum key value (inclusive).
  /// @param minValue The minimum value (inclusive).
  /// @param maxValue The maximum value (inclusive).
  /// @param size The number of key-value pairs to generate.
  /// @return A map containing the generated key-value pairs.
  template <typename T, typename U>
  static auto generateMap(T minKey, T maxKey, U minValue, U maxValue, int32_t size) -> std::map<T, U>;

  /// @brief Generate a multimap with random key-value pairs within the specified ranges.
  /// @tparam T The type of the keys.
  /// @tparam U The type of the values.
  /// @param minKey The minimum key value (inclusive).
  /// @param maxKey The maximum key value (inclusive).
  /// @param minValue The minimum value (inclusive).
  /// @param maxValue The maximum value (inclusive).
  /// @param size The number of key-value pairs to generate.
  /// @return A multimap containing the generated key-value pairs.
  template <typename T, typename U>
  static auto generateMultiMap(T minKey, T maxKey, U minValue, U maxValue, int32_t size) -> std::multimap<T, U>;

  /// @brief Generate an unordered map with random key-value pairs within the specified ranges.
  /// @tparam T The type of the keys.
  /// @tparam U The type of the values.
  /// @param minKey The minimum key value (inclusive).
  /// @param maxKey The maximum key value (inclusive).
  /// @param minValue The minimum value (inclusive).
  /// @param maxValue The maximum value (inclusive).
  /// @param size The number of key-value pairs to generate.
  /// @return An unordered map containing the generated key-value pairs.
  template <typename T, typename U>
  static auto generateUnorderedMap(T minKey, T maxKey, U minValue, U maxValue, int32_t size) -> std::unordered_map<T, U>;

  /// @brief Generate an unordered multimap with random key-value pairs within the specified ranges.
  /// @tparam T The type of the keys.
  /// @tparam U The type of the values.
  /// @param minKey The minimum key value (inclusive).
  /// @param maxKey The maximum key value (inclusive).
  /// @param minValue The minimum value (inclusive).
  /// @param maxValue The maximum value (inclusive).
  /// @param size The number of key-value pairs to generate.
  /// @return An unordered multimap containing the generated key-value pairs.
  template <typename T, typename U>
  static auto generateUnorderedMultiMap(T minKey, T maxKey, U minValue, U maxValue, int32_t size) -> std::unordered_multimap<T, U>;

 private:
  static inline auto mt1993764_ = std::mt19937_64(std::random_device{}());

  /// @brief Generate a random value within the specified range.
  /// @tparam T The type of the value.
  /// @param minValue The minimum value (inclusive).
  /// @param maxValue The maximum value (inclusive).
  /// @return A random value within the specified range.
  template <typename T>
  static auto NextValue(T minValue, T maxValue) -> T;

  /// @brief Check if the parameters are valid.
  /// @tparam T The type of the values.
  /// @param minValue The minimum value.
  /// @param maxValue The maximum value.
  /// @param size The size of the container.
  template <typename T>
  static auto Check(T minValue, T maxValue, int32_t size) -> void;
};

template <typename T>
auto ContainerGenerator::generateVector(T minValue, T maxValue, int32_t size) -> std::vector<T> {
  Check(minValue, maxValue, size);
  std::vector<T> result;
  result.reserve(size);
  for (size_t i = 0; i < size; i++) {
    result.emplace_back(NextValue<T>(minValue, maxValue));
  }
  return result;
}

template <typename T>
auto ContainerGenerator::generateDeque(T minValue, T maxValue, int32_t size) -> std::deque<T> {
  Check(minValue, maxValue, size);
  std::deque<T> result;
  for (size_t i = 0; i < size; i++) {
    result.emplace_back(NextValue<T>(minValue, maxValue));
  }
  return result;
}

template <typename T>
auto ContainerGenerator::generateList(T minValue, T maxValue, int32_t size) -> std::list<T> {
  Check(minValue, maxValue, size);
  std::list<T> result;
  for (size_t i = 0; i < size; i++) {
    result.emplace_back(NextValue<T>(minValue, maxValue));
  }
  return result;
}

template <typename T>
auto ContainerGenerator::generateForwardList(T minValue, T maxValue, int32_t size) -> std::forward_list<T> {
  Check(minValue, maxValue, size);
  std::forward_list<T> result;
  for (size_t i = 0; i < size; i++) {
    result.emplace_front(NextValue<T>(minValue, maxValue));
  }
  return result;
}

template <typename T, size_t N>
auto ContainerGenerator::generateArray(T minValue, T maxValue) -> std::array<T, N> {
  Check(minValue, maxValue, N);
  std::array<T, N> result;
  for (size_t i = 0; i < N; i++) {
    result[i] = NextValue<T>(minValue, maxValue);
  }
  return result;
}

template <typename T>
auto ContainerGenerator::generateSet(T minValue, T maxValue, int32_t size) -> std::set<T> {
  Check(minValue, maxValue, size);
  std::set<T> result;
  for (size_t i = 0; i < size; i++) {
    result.emplace(NextValue<T>(minValue, maxValue));
  }
  return result;
}

template <typename T>
auto ContainerGenerator::generateUnorderedSet(T minValue, T maxValue, int32_t size) -> std::unordered_set<T> {
  Check(minValue, maxValue, size);
  std::unordered_set<T> result;
  for (size_t i = 0; i < size; i++) {
    result.emplace(NextValue<T>(minValue, maxValue));
  }
  return result;
}

template <typename T>
auto ContainerGenerator::generateMultiSet(T minValue, T maxValue, int32_t size) -> std::multiset<T> {
  Check(minValue, maxValue, size);
  std::multiset<T> result;
  for (size_t i = 0; i < size; i++) {
    result.emplace(NextValue<T>(minValue, maxValue));
  }
  return result;
}

template <typename T>
auto ContainerGenerator::generateUnorderedMultiSet(T minValue, T maxValue, int32_t size) -> std::unordered_multiset<T> {
  Check(minValue, maxValue, size);
  std::unordered_multiset<T> result;
  for (size_t i = 0; i < size; i++) {
    result.emplace(NextValue<T>(minValue, maxValue));
  }
  return result;
}

template <typename T, typename U>
auto ContainerGenerator::generateMap(T minKey, T maxKey, U minValue, U maxValue, int32_t size) -> std::map<T, U> {
  Check(minKey, maxKey, size);
  Check(minValue, maxValue, size);
  std::map<T, U> result;
  for (size_t i = 0; i < size; i++) {
    result.emplace(NextValue<T>(minKey, maxKey), NextValue<U>(minValue, maxValue));
  }
  return result;
}

template <typename T, typename U>
auto ContainerGenerator::generateMultiMap(T minKey, T maxKey, U minValue, U maxValue, int32_t size) -> std::multimap<T, U> {
  Check(minKey, maxKey, size);
  Check(minValue, maxValue, size);
  std::multimap<T, U> result;
  for (size_t i = 0; i < size; i++) {
    result.emplace(NextValue<T>(minKey, maxKey), NextValue<U>(minValue, maxValue));
  }
  return result;
}

template <typename T, typename U>
auto ContainerGenerator::generateUnorderedMap(T minKey, T maxKey, U minValue, U maxValue, int32_t size) -> std::unordered_map<T, U> {
  Check(minKey, maxKey, size);
  Check(minValue, maxValue, size);
  std::unordered_map<T, U> result;
  for (size_t i = 0; i < size; i++) {
    result.emplace(NextValue<T>(minKey, maxKey), NextValue<U>(minValue, maxValue));
  }
  return result;
}

template <typename T, typename U>
auto ContainerGenerator::generateUnorderedMultiMap(T minKey, T maxKey, U minValue, U maxValue, int32_t size) -> std::unordered_multimap<T, U> {
  Check(minKey, maxKey, size);
  Check(minValue, maxValue, size);
  std::unordered_multimap<T, U> result;
  for (size_t i = 0; i < size; i++) {
    result.emplace(NextValue<T>(minKey, maxKey), NextValue<U>(minValue, maxValue));
  }
  return result;
}

template <typename T>
auto ContainerGenerator::NextValue(T minValue, T maxValue) -> T {
  if constexpr (std::is_integral_v<T>) {
    static std::uniform_int_distribution<T> keyGen(minValue, maxValue);
    return keyGen(mt1993764_);
  } else if constexpr (std::is_floating_point_v<T>) {
    static std::uniform_real_distribution<T> keyGen(minValue, maxValue);
    return keyGen(mt1993764_);
  } else {
    throw std::invalid_argument("unsupported type");
  }
}

template <typename T>
auto ContainerGenerator::Check(T minValue, T maxValue, const int32_t size) -> void {
  if (minValue > maxValue || size < 0) {
    throw std::invalid_argument("ContainerGenerator: invalid parameters");
  }
}
}  // namespace fox
