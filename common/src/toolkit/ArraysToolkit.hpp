#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include <cstdint>

namespace common
{
    /// @brief Utility class for array operations.
    /// @details This class provides static methods to perform various operations on arrays,
    ///          such as converting to a vector, binary search, copying, comparison, filling,
    ///          sorting, and generating string representations.
    class ArraysToolkit
    {
    public:
        /// @brief Converts an array to a vector.
        /// @tparam T The type of elements in the array.
        /// @param array Pointer to the array.
        /// @param size Size of the array.
        /// @return A vector containing the elements of the array.
        template <typename T>
        [[nodiscard]] static auto asList(const T* array, size_t size) -> std::vector<T>;

        /// @brief Searches for a key in a sorted array using binary search.
        /// @tparam T The type of elements in the array.
        /// @param array Pointer to the sorted array.
        /// @param size Size of the array.
        /// @param key The value to search for.
        /// @return Index of the key if found, otherwise -1.
        template <typename T>
        [[nodiscard]] static auto binarySearch(const T* array, size_t size, const T& key) -> int32_t;

        /// @brief Searches for a key in a sorted subarray using binary search.
        /// @tparam T The type of elements in the array.
        /// @param array Pointer to the sorted array.
        /// @param fromIndex Starting index of the subarray (inclusive).
        /// @param toIndex Ending index of the subarray (exclusive).
        /// @param key The value to search for.
        /// @return Index of the key if found, otherwise -1.
        /// @throws std::out_of_range If fromIndex >= toIndex
        template <typename T>
        [[nodiscard]] static auto binarySearch(const T* array, size_t fromIndex, size_t toIndex,
                                               const T& key) -> int32_t;

        /// @brief Copies an array to a new vector of specified length.
        /// @tparam T The type of elements in the array.
        /// @param original Pointer to the original array.
        /// @param originalSize Size of the original array.
        /// @param newLength Length of the new vector.
        /// @return A new vector with the copied elements.
        template <typename T>
        [[nodiscard]] static auto copyOf(const T* original, size_t originalSize, size_t newLength) -> std::vector<T>;

        /// @brief Copies a range of an array to a new vector.
        /// @tparam T The type of elements in the array.
        /// @param original Pointer to the original array.
        /// @param from Starting index (inclusive).
        /// @param to Ending index (exclusive).
        /// @return A new vector containing the specified range.
        /// @throws std::out_of_range If from > to
        template <typename T>
        [[nodiscard]] static auto copyOfRange(const T* original, size_t from, size_t to) -> std::vector<T>;

        /// @brief Checks if two arrays are equal.
        /// @tparam T The type of elements in the arrays.
        /// @param a Pointer to the first array.
        /// @param sizeA Size of the first array.
        /// @param b Pointer to the second array.
        /// @param sizeB Size of the second array.
        /// @return True if the arrays are equal, false otherwise.
        template <typename T>
        [[nodiscard]] static auto equals(const T* a, size_t sizeA, const T* b, size_t sizeB) -> bool;

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
        /// @throws std::out_of_range If fromIndex >= toIndex
        template <typename T>
        static auto sort(T* array, size_t fromIndex, size_t toIndex) -> void;

        /// @brief Converts an array to a string representation.
        /// @tparam T The type of elements in the array.
        /// @param array Pointer to the array.
        /// @param size Size of the array.
        /// @return A string representation of the array.
        template <typename T>
        [[nodiscard]] static auto toString(const T* array, size_t size) -> std::string;
    };
}
