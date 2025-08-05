#pragma once
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

namespace common {
/// @brief Utility class for array operations.
/// @details This class provides static methods to perform various operations on arrays,
///          such as converting to a vector, binary search, copying, comparison, filling,
///          sorting, and generating string representations.
class ArraysUtil abstract {
 public:
  /// @brief Converts an array to a vector.
  /// @tparam T The type of elements in the array.
  /// @param array Pointer to the array.
  /// @param size Size of the array.
  /// @return A vector containing the elements of the array.
  template <typename T>
  static auto asList(const T* array, size_t size) -> std::vector<T>;

  /// @brief Searches for a key in a sorted array using binary search.
  /// @tparam T The type of elements in the array.
  /// @param array Pointer to the sorted array.
  /// @param size Size of the array.
  /// @param key The value to search for.
  /// @return Index of the key if found, otherwise -1.
  template <typename T>
  static auto binarySearch(const T* array, size_t size, const T& key) -> int32_t;

  /// @brief Searches for a key in a sorted subarray using binary search.
  /// @tparam T The type of elements in the array.
  /// @param array Pointer to the sorted array.
  /// @param fromIndex Starting index of the subarray (inclusive).
  /// @param toIndex Ending index of the subarray (exclusive).
  /// @param key The value to search for.
  /// @return Index of the key if found, otherwise -1.
  template <typename T>
  static auto binarySearch(const T* array, size_t fromIndex, size_t toIndex, const T& key) -> int32_t;

  /// @brief Copies an array to a new vector of specified length.
  /// @tparam T The type of elements in the array.
  /// @param original Pointer to the original array.
  /// @param originalSize Size of the original array.
  /// @param newLength Length of the new vector.
  /// @return A new vector with the copied elements.
  template <typename T>
  static auto copyOf(const T* original, size_t originalSize, size_t newLength) -> std::vector<T>;

  /// @brief Copies a range of an array to a new vector.
  /// @tparam T The type of elements in the array.
  /// @param original Pointer to the original array.
  /// @param from Starting index (inclusive).
  /// @param to Ending index (exclusive).
  /// @return A new vector containing the specified range.
  template <typename T>
  static auto copyOfRange(const T* original, size_t from, size_t to) -> std::vector<T>;

  /// @brief Checks if two arrays are equal.
  /// @tparam T The type of elements in the arrays.
  /// @param a Pointer to the first array.
  /// @param sizeA Size of the first array.
  /// @param b Pointer to the second array.
  /// @param sizeB Size of the second array.
  /// @return True if the arrays are equal, false otherwise.
  template <typename T>
  static auto equals(const T* a, size_t sizeA, const T* b, size_t sizeB) -> bool;

  /// @brief Fills an array with a specific value.
  /// @tparam T The type of elements in the array.
  /// @param array Pointer to the array.
  /// @param size Size of the array.
  /// @param value The value to fill the array with.
  template <typename T>
  static auto fill(T* array, size_t size, const T& value) -> void;

  /// @brief Sorts an array in ascending order.
  /// @tparam T The type of elements in the array.
  /// @param array Pointer to the array.
  /// @param size Size of the array.
  template <typename T>
  static auto sort(T* array, size_t size) -> void;

  /// @brief Sorts a subarray in ascending order.
  /// @tparam T The type of elements in the array.
  /// @param array Pointer to the array.
  /// @param fromIndex Starting index of the subarray (inclusive).
  /// @param toIndex Ending index of the subarray (exclusive).
  template <typename T>
  static auto sort(T* array, size_t fromIndex, size_t toIndex) -> void;

  /// @brief Converts an array to a string representation.
  /// @tparam T The type of elements in the array.
  /// @param array Pointer to the array.
  /// @param size Size of the array.
  /// @return A string representation of the array.
  template <typename T>
  static auto toString(const T* array, size_t size) -> std::string;
};

template <typename T>
auto ArraysUtil::asList(const T* array, size_t size) -> std::vector<T> {
  return std::vector<T>(array, array + size);
}

template <typename T>
auto ArraysUtil::binarySearch(const T* array, size_t size, const T& key) -> int32_t {
  auto it = std::lower_bound(array, array + size, key);
  if (it != array + size && *it == key) {
    return static_cast<int32_t>(it - array);
  }
  return -1;
}

template <typename T>
auto ArraysUtil::binarySearch(const T* array, size_t fromIndex, size_t toIndex, const T& key) -> int32_t {
  if (fromIndex >= toIndex) throw std::out_of_range("Invalid range");
  auto start = array + fromIndex;
  auto end = array + toIndex;
  auto it = std::lower_bound(start, end, key);
  if (it != end && *it == key) {
    return static_cast<int32_t>(it - array);
  }
  return -1;
}

template <typename T>
auto ArraysUtil::copyOf(const T* original, const size_t originalSize, size_t newLength) -> std::vector<T> {
  std::vector<T> result(newLength);
  size_t copyLength = std::min(originalSize, newLength);
  std::copy(original, original + copyLength, result.begin());
  return result;
}

template <typename T>
auto ArraysUtil::copyOfRange(const T* original, size_t from, size_t to) -> std::vector<T> {
  if (from > to) throw std::out_of_range("Invalid range");
  return std::vector<T>(original + from, original + to);
}

template <typename T>
auto ArraysUtil::equals(const T* a, size_t sizeA, const T* b, const size_t sizeB) -> bool {
  if (sizeA != sizeB) return false;
  return std::equal(a, a + sizeA, b);
}

template <typename T>
auto ArraysUtil::fill(T* array, size_t size, const T& value) -> void {
  std::fill(array, array + size, value);
}

template <typename T>
auto ArraysUtil::sort(T* array, size_t size) -> void {
  std::sort(array, array + size);
}

template <typename T>
auto ArraysUtil::sort(T* array, size_t fromIndex, size_t toIndex) -> void {
  if (fromIndex >= toIndex) throw std::out_of_range("Invalid range");
  std::sort(array + fromIndex, array + toIndex);
}

template <typename T>
auto ArraysUtil::toString(const T* array, const size_t size) -> std::string {
  std::ostringstream oss;
  oss << "[";
  for (size_t i = 0; i < size; ++i) {
    oss << array[i];
    if (i < size - 1) oss << ", ";
  }
  oss << "]";
  return oss.str();
}
}  // namespace common
