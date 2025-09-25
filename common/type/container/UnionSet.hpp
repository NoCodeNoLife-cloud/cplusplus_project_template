#pragma once
#include <unordered_map>
#include <cstdint>

namespace fox
{
    /// @brief A Union-Find (Disjoint Set Union) data structure implementation.
    /// This class provides efficient operations for disjoint sets, including:
    /// - Finding the root of a set with path compression
    /// - Uniting two sets with union by rank
    /// - Checking if two elements are in the same set
    ///
    /// The implementation uses two hash maps:
    /// - [parent](file://E:\GitHub\cplusplus_project_template\common\type\container\UnionSet.hpp#L36-L36): Maps each element to its parent in the set
    /// - [rank](file://E:\GitHub\cplusplus_project_template\common\type\container\UnionSet.hpp#L37-L37): Maps each element to its rank (used for union by rank optimization)
    template <typename T>
    class UnionSet
    {
    public:
        /// @brief Finds the root of the set containing element x with path compression.
        /// @param x The element to find the root for.
        /// @return The root of the set containing element x.
        auto find(const T& x) -> T;

        /// @brief Unites the sets that contain elements x and y.
        /// @param x First element
        /// @param y Second element
        /// @return True if the sets were successfully united, false if they were already in the same set.
        [[nodiscard]] auto unionSets(const T& x, const T& y) -> bool;

        /// @brief Checks if elements x and y are in the same set.
        /// @param x First element
        /// @param y Second element
        /// @return True if x and y are connected (in the same set), false otherwise.
        [[nodiscard]] auto connected(const T& x, const T& y) const -> bool;

    private:
        /// @brief Ensures that the element x is registered in the UnionSet.
        /// @param x The element to register.
        auto ensureRegistered(const T& x) const -> void;

        std::unordered_map<T, T> parent_{};
        std::unordered_map<T, int32_t> rank_{};
    };

    template <typename T>
    auto UnionSet<T>::find(const T& x) -> T
    {
        ensureRegistered(x);
        if (parent_[x] != x)
        {
            parent_[x] = find(parent_[x]);
        }
        return parent_[x];
    }

    template <typename T>
    auto UnionSet<T>::unionSets(const T& x, const T& y) -> bool
    {
        T rootX = find(x);
        T rootY = find(y);

        if (rootX == rootY)
            return false;

        if (rank_[rootX] < rank_[rootY])
        {
            parent_[rootX] = rootY;
        }
        else if (rank_[rootX] > rank_[rootY])
        {
            parent_[rootY] = rootX;
        }
        else
        {
            parent_[rootY] = rootX;
            ++rank_[rootX];
        }
        return true;
    }

    template <typename T>
    auto UnionSet<T>::connected(const T& x, const T& y) const -> bool
    {
        // Create temporary instances to register elements if needed
        // This approach avoids const_cast and maintains const correctness
        UnionSet* self = const_cast<UnionSet*>(this);
        self->ensureRegistered(x);
        self->ensureRegistered(y);
        return self->find(x) == self->find(y);
    }

    template <typename T>
    auto UnionSet<T>::ensureRegistered(const T& x) const -> void
    {
        if (!parent_.contains(x))
        {
            parent_[x] = x;
            rank_[x] = 0;
        }
    }
}
