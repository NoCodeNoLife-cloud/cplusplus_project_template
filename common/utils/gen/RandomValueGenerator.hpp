#pragma once
#include <random>
#include <type_traits>
#include <algorithm>
#include <cstdint>

namespace fox
{
    /// @brief A class template for generating random values of integral or floating-point types.
    /// @tparam T The type of the values to generate. Must be an integral or floating-point type.
    template <typename T>
    concept ValidType = std::is_integral_v<T> || std::is_floating_point_v<T>;

    /// @brief A class template for generating random values of integral or floating-point types.
    /// @tparam T The type of the values to generate. Must be an integral or floating-point type.
    template <ValidType T>
    class RandomValueGenerator
    {
    public:
        RandomValueGenerator();

        explicit RandomValueGenerator(const std::mt19937::result_type& seed) noexcept;

        /// @brief Generates a random value between min and max (inclusive).
        /// @param min The minimum value.
        /// @param max The maximum value.
        /// @return A random value of type T between min and max.
        [[nodiscard]] auto generate(T min, T max) -> T;

    private:
        std::mt19937 engine_;
    };

    template <ValidType T>
    RandomValueGenerator<T>::RandomValueGenerator()
    {
        std::random_device rd;
        std::seed_seq seed_seq{rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()};
        engine_.seed(seed_seq);
    }

    template <ValidType T>
    RandomValueGenerator<T>::RandomValueGenerator(const std::mt19937::result_type& seed) noexcept : engine_(seed)
    {
    }

    template <ValidType T>
    auto RandomValueGenerator<T>::generate(T min, T max) -> T
    {
        if (min > max)
        {
            std::swap(min, max);
        }

        if constexpr (std::is_floating_point_v<T>)
        {
            std::uniform_real_distribution<T> dist(min, max);
            return dist(engine_);
        }
        else
        {
            std::uniform_int_distribution<T> dist(min, max);
            return dist(engine_);
        }
    }
} // namespace fox
