#pragma once
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

namespace common {
class ArraysUtil abstract {
 public:
  template <typename T>
  static auto asList(const T* array, size_t size) -> std::vector<T>;
  template <typename T>
  static auto binarySearch(const T* array, size_t size, const T& key)
      -> int32_t;
  template <typename T>
  static auto binarySearch(const T* array, size_t fromIndex, size_t toIndex,
                           const T& key) -> int32_t;
  template <typename T>
  static auto copyOf(const T* original, size_t originalSize, size_t newLength)
      -> std::vector<T>;
  template <typename T>
  static auto copyOfRange(const T* original, size_t from, size_t to)
      -> std::vector<T>;
  template <typename T>
  static auto equals(const T* a, size_t sizeA, const T* b, size_t sizeB)
      -> bool;
  template <typename T>
  static auto fill(T* array, size_t size, const T& value) -> void;
  template <typename T>
  static auto sort(T* array, size_t size) -> void;
  template <typename T>
  static auto sort(T* array, size_t fromIndex, size_t toIndex) -> void;
  template <typename T>
  static auto toString(const T* array, size_t size) -> std::string;
};

template <typename T>
auto ArraysUtil::asList(const T* array, size_t size) -> std::vector<T> {
  return std::vector<T>(array, array + size);
}

template <typename T>
auto ArraysUtil::binarySearch(const T* array, size_t size, const T& key)
    -> int32_t {
  auto it = std::lower_bound(array, array + size, key);
  if (it != array + size && *it == key) {
    return static_cast<int32_t>(it - array);
  }
  return -1;
}

template <typename T>
auto ArraysUtil::binarySearch(const T* array, size_t fromIndex, size_t toIndex,
                              const T& key) -> int32_t {
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
auto ArraysUtil::copyOf(const T* original, const size_t originalSize,
                        size_t newLength) -> std::vector<T> {
  std::vector<T> result(newLength);
  size_t copyLength = std::min(originalSize, newLength);
  std::copy(original, original + copyLength, result.begin());
  return result;
}

template <typename T>
auto ArraysUtil::copyOfRange(const T* original, size_t from, size_t to)
    -> std::vector<T> {
  if (from > to) throw std::out_of_range("Invalid range");
  return std::vector<T>(original + from, original + to);
}

template <typename T>
auto ArraysUtil::equals(const T* a, size_t sizeA, const T* b,
                        const size_t sizeB) -> bool {
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
