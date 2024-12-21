#pragma once
#include "type/data_structure/graphics/Graph.hpp"

namespace common
{
    class Dijkstra
    {
    public:
        explicit Dijkstra(const Graph& g);
        auto compute(int32_t start) -> void;
        [[nodiscard]] auto getDistance(int32_t node) const -> int32_t;
        [[nodiscard]] auto getDistances() const -> std::vector<int32_t>;

    private:
        const Graph& graph_;
        std::vector<int32_t> distances_;
        const int32_t INF = std::numeric_limits<int32_t>::max();
    };
}
