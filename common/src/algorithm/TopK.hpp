#pragma once
#include <queue>
#include <vector>

namespace fox
{
    /// @brief A class to maintain the top K the largest numbers from a stream of integers.
    /// The TopK class uses a min-heap to efficiently track the top K the largest numbers.
    /// When a new number is added, it is compared with the smallest number in the heap.
    /// If the new number is larger, the smallest number is removed and the new number is added.
    /// This ensures that the heap always contains the top K the largest numbers seen so far.
    class TopK final
    {
    public:
        explicit TopK(int32_t k);

        /// @brief Add a number to the TopK.
        /// @param num The number to add.
        auto add(int32_t num) -> void;

        /// @brief Get the top k numbers.
        /// @return The top k numbers.
        auto getTopK() -> std::vector<int32_t>;

    private:
        int32_t k;
        std::priority_queue<int32_t, std::vector<int32_t>, std::greater<>> minHeap;
    };
}
