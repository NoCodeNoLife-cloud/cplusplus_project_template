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

namespace coco
{
    class ContainerGenerator abstract
    {
    public:
        template <typename T>
        static auto generateVector(T minValue, T maxValue, int32_t size) -> std::vector<T>;
        template <typename T>
        static auto generateDeque(T minValue, T maxValue, int32_t size) -> std::deque<T>;
        template <typename T>
        static auto generateList(T minValue, T maxValue, int32_t size) -> std::list<T>;
        template <typename T>
        static auto generateForwardList(T minValue, T maxValue, int32_t size) -> std::forward_list<T>;
        template <typename T, size_t N>
        static auto generateArray(T minValue, T maxValue) -> std::array<T, N>;
        template <typename T>
        static auto generateSet(T minValue, T maxValue, int32_t size) -> std::set<T>;
        template <typename T>
        static auto generateUnorderedSet(T minValue, T maxValue, int32_t size) -> std::unordered_set<T>;
        template <typename T>
        static auto generateMultiSet(T minValue, T maxValue, int32_t size) -> std::multiset<T>;
        template <typename T>
        static auto generateUnorderedMultiSet(T minValue, T maxValue, int32_t size) -> std::unordered_multiset<T>;
        template <typename T, typename U>
        static auto generateMap(T minKey, T maxKey, U minValue, U maxValue, int32_t size) -> std::map<T, U>;
        template <typename T, typename U>
        static auto generateMultiMap(T minKey, T maxKey, U minValue, U maxValue, int32_t size) -> std::multimap<T, U>;
        template <typename T, typename U>
        static auto generateUnorderedMap(T minKey, T maxKey, U minValue, U maxValue, int32_t size) -> std::unordered_map<T, U>;
        template <typename T, typename U>
        static auto generateUnorderedMultiMap(T minKey, T maxKey, U minValue, U maxValue, int32_t size) -> std::unordered_multimap<T, U>;

    private:
        static inline auto mt1993764_ = std::mt19937_64(std::random_device{}());
        template <typename T>
        static auto NextValue(T minValue, T maxValue) -> T;
        template <typename T>
        static auto Check(T minValue, T maxValue, int32_t size) -> void;
    };

    template <typename T>
    auto ContainerGenerator::generateVector(T minValue, T maxValue, int32_t size) -> std::vector<T>
    {
        Check(minValue, maxValue, size);
        std::vector<T> result;
        result.reserve(size);
        for (size_t i = 0; i < size; i++)
        {
            result.emplace_back(NextValue<T>(minValue, maxValue));
        }
        return result;
    }

    template <typename T>
    auto ContainerGenerator::generateDeque(T minValue, T maxValue, int32_t size) -> std::deque<T>
    {
        Check(minValue, maxValue, size);
        std::deque<T> result;
        for (size_t i = 0; i < size; i++)
        {
            result.emplace_back(NextValue<T>(minValue, maxValue));
        }
        return result;
    }

    template <typename T>
    auto ContainerGenerator::generateList(T minValue, T maxValue, int32_t size) -> std::list<T>
    {
        Check(minValue, maxValue, size);
        std::list<T> result;
        for (size_t i = 0; i < size; i++)
        {
            result.emplace_back(NextValue<T>(minValue, maxValue));
        }
        return result;
    }

    template <typename T>
    auto ContainerGenerator::generateForwardList(T minValue, T maxValue, int32_t size) -> std::forward_list<T>
    {
        Check(minValue, maxValue, size);
        std::forward_list<T> result;
        for (size_t i = 0; i < size; i++)
        {
            result.emplace_front(NextValue<T>(minValue, maxValue));
        }
        return result;
    }

    template <typename T, size_t N>
    auto ContainerGenerator::generateArray(T minValue, T maxValue) -> std::array<T, N>
    {
        Check(minValue, maxValue, N);
        std::array<T, N> result;
        for (size_t i = 0; i < N; i++)
        {
            result[i] = NextValue<T>(minValue, maxValue);
        }
        return result;
    }

    template <typename T>
    auto ContainerGenerator::generateSet(T minValue, T maxValue, int32_t size) -> std::set<T>
    {
        Check(minValue, maxValue, size);
        std::set<T> result;
        for (size_t i = 0; i < size; i++)
        {
            result.emplace(NextValue<T>(minValue, maxValue));
        }
        return result;
    }

    template <typename T>
    auto ContainerGenerator::generateUnorderedSet(T minValue, T maxValue, int32_t size) -> std::unordered_set<T>
    {
        Check(minValue, maxValue, size);
        std::unordered_set<T> result;
        for (size_t i = 0; i < size; i++)
        {
            result.emplace(NextValue<T>(minValue, maxValue));
        }
        return result;
    }

    template <typename T>
    auto ContainerGenerator::generateMultiSet(T minValue, T maxValue, int32_t size) -> std::multiset<T>
    {
        Check(minValue, maxValue, size);
        std::multiset<T> result;
        for (size_t i = 0; i < size; i++)
        {
            result.emplace(NextValue<T>(minValue, maxValue));
        }
        return result;
    }

    template <typename T>
    auto ContainerGenerator::generateUnorderedMultiSet(T minValue, T maxValue, int32_t size)
        -> std::unordered_multiset<T>
    {
        Check(minValue, maxValue, size);
        std::unordered_multiset<T> result;
        for (size_t i = 0; i < size; i++)
        {
            result.emplace(NextValue<T>(minValue, maxValue));
        }
        return result;
    }

    template <typename T, typename U>
    auto ContainerGenerator::generateMap(T minKey, T maxKey, U minValue, U maxValue, int32_t size) -> std::map<T, U>
    {
        Check(minKey, maxKey, size);
        Check(minValue, maxValue, size);
        std::map<T, U> result;
        for (size_t i = 0; i < size; i++)
        {
            result.emplace(NextValue<T>(minKey, maxKey), NextValue<U>(minValue, maxValue));
        }
        return result;
    }

    template <typename T, typename U>
    auto ContainerGenerator::generateMultiMap(T minKey, T maxKey, U minValue, U maxValue, int32_t size)
        -> std::multimap<T, U>
    {
        Check(minKey, maxKey, size);
        Check(minValue, maxValue, size);
        std::multimap<T, U> result;
        for (size_t i = 0; i < size; i++)
        {
            result.emplace(NextValue<T>(minKey, maxKey), NextValue<U>(minValue, maxValue));
        }
        return result;
    }

    template <typename T, typename U>
    auto ContainerGenerator::generateUnorderedMap(T minKey, T maxKey, U minValue, U maxValue, int32_t size)
        -> std::unordered_map<T, U>
    {
        Check(minKey, maxKey, size);
        Check(minValue, maxValue, size);
        std::unordered_map<T, U> result;
        for (size_t i = 0; i < size; i++)
        {
            result.emplace(NextValue<T>(minKey, maxKey), NextValue<U>(minValue, maxValue));
        }
        return result;
    }

    template <typename T, typename U>
    auto ContainerGenerator::generateUnorderedMultiMap(T minKey, T maxKey, U minValue, U maxValue, int32_t size)
        -> std::unordered_multimap<T, U>
    {
        Check(minKey, maxKey, size);
        Check(minValue, maxValue, size);
        std::unordered_multimap<T, U> result;
        for (size_t i = 0; i < size; i++)
        {
            result.emplace(NextValue<T>(minKey, maxKey), NextValue<U>(minValue, maxValue));
        }
        return result;
    }

    template <typename T>
    auto ContainerGenerator::NextValue(T minValue, T maxValue) -> T
    {
        if constexpr (std::is_integral_v<T>)
        {
            static std::uniform_int_distribution<T> keyGen(minValue, maxValue);
            return keyGen(mt1993764_);
        }
        else if constexpr (std::is_floating_point_v<T>)
        {
            static std::uniform_real_distribution<T> keyGen(minValue, maxValue);
            return keyGen(mt1993764_);
        }
        else
        {
            throw std::invalid_argument("unsupported type");
        }
    }

    template <typename T>
    auto ContainerGenerator::Check(T minValue, T maxValue, const int32_t size) -> void
    {
        if (minValue > maxValue || size < 0)
        {
            throw std::invalid_argument("ContainerGenerator: invalid parameters");
        }
    }
}
