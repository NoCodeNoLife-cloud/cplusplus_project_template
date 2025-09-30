#pragma once
#include <cstdint>

namespace fox
{
    /// @brief Data structure for representing an edge in a graph
    /// @details This class stores information about an edge, including
    ///          the target vertex and the weight of the edge. It provides
    ///          methods to get and set these values.
    class Edge
    {
    public:
        /// @brief Construct an Edge with target vertex and weight
        /// @param to Target vertex
        /// @param weight Edge weight
        explicit Edge(int32_t to, int32_t weight) noexcept;

        /// @brief Get target vertex
        /// @return Target vertex
        [[nodiscard]] auto to() const noexcept -> int32_t;

        /// @brief Set target vertex
        /// @param to Target vertex
        auto setTo(int32_t to) noexcept -> void;

        /// @brief Get edge weight
        /// @return Edge weight
        [[nodiscard]] auto weight() const noexcept -> int32_t;

        /// @brief Set edge weight
        /// @param weight Edge weight
        auto setWeight(int32_t weight) noexcept -> void;

    private:
        int32_t to_{0};
        int32_t weight_{0};
    };

    inline Edge::Edge(const int32_t to, const int32_t weight) noexcept : to_(to), weight_(weight)
    {
    }

    inline auto Edge::to() const noexcept -> int32_t
    {
        return to_;
    }

    inline auto Edge::setTo(const int32_t to) noexcept -> void
    {
        to_ = to;
    }

    inline auto Edge::weight() const noexcept -> int32_t
    {
        return weight_;
    }

    inline auto Edge::setWeight(const int32_t weight) noexcept -> void
    {
        weight_ = weight;
    }
}
