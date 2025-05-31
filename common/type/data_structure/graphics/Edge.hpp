#pragma once
#include <cstdint>

namespace common
{
    class Edge
    {
    public:
        Edge(int32_t to, int32_t weight);
        [[nodiscard]] auto to() const -> int32_t;
        [[nodiscard]] auto weight() const -> int32_t;
        auto setTo(int32_t to) -> void;
        auto setWeight(int32_t weight) -> void;

    private:
        int32_t to_{0};
        int32_t weight_{0};
    };
}
