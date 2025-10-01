#include "src/algorithm/Dijkstra.hpp"
#include <functional>
#include <queue>
#include <type_traits>
#include <vector>

namespace fox
{
    template <typename GraphType, typename DistanceType>
    Dijkstra<GraphType, DistanceType>::Dijkstra(const GraphType& g) : graph_(g)
    {
        distances_.resize(graph_.getNodeCount(), INF);
    }

    template <typename GraphType, typename DistanceType>
    template <typename DistanceFunc>
    auto Dijkstra<GraphType, DistanceType>::compute(
        std::decay_t<decltype(std::declval<GraphType>().getNodeCount())> start,
        DistanceFunc distanceFunc) -> void
    {
        std::fill(distances_.begin(), distances_.end(), INF);
        distances_[start] = DistanceType{0};

        std::priority_queue<
                std::pair<DistanceType, std::decay_t<decltype(std::declval<GraphType>().getNodeCount())>>,
                std::vector<std::pair<DistanceType, std::decay_t<decltype(std::declval<GraphType>().getNodeCount())>>>,
                std::greater<>>
            pq;

        pq.emplace(DistanceType{0}, start);

        while (!pq.empty())
        {
            const DistanceType currentDist = pq.top().first;
            const std::decay_t<decltype(std::declval<GraphType>().getNodeCount())> u = pq.top().second;
            pq.pop();

            if (currentDist > distances_[u])
                continue;

            for (const auto& e : graph_.getAdjList(u))
            {
                std::decay_t<decltype(std::declval<GraphType>().getNodeCount())> v = e.to();
                DistanceType edgeWeight = distanceFunc(e);
                if (DistanceType newDist = currentDist + edgeWeight; newDist < distances_[v])
                {
                    distances_[v] = newDist;
                    pq.emplace(newDist, v);
                }
            }
        }
    }

    template <typename GraphType, typename DistanceType>
    auto Dijkstra<GraphType, DistanceType>::getDistance(
        const std::decay_t<decltype(std::declval<GraphType>().getNodeCount())> node) const -> DistanceType
    {
        return distances_[node];
    }

    template <typename GraphType, typename DistanceType>
    auto Dijkstra<GraphType, DistanceType>::getDistances() const -> const std::vector<DistanceType>&
    {
        return distances_;
    }

    // Explicit template instantiation would be needed in a real-world scenario
    // For example, if you know the specific types that will be used:
    // template class Dijkstra<SomeGraphType, int>;
}
