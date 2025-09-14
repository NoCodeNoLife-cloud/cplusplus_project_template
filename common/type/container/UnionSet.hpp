#pragma once
#include <unordered_map>

namespace fox
{
/// @brief A Union-Find (Disjoint Set Union) data structure implementation.
/// This class provides efficient operations for disjoint sets, including:
/// - Finding the root of a set with path compression
/// - Uniting two sets with union by rank
/// - Checking if two elements are in the same set
///
/// The implementation uses two hash maps:
/// - `parent`: Maps each element to its parent in the set
/// - `rank`: Maps each element to its rank (used for union by rank optimization)
template <typename T> class UnionSet
{
  public:
    /// @brief Finds the root of the set containing element x with path compression.
    /// @param x The element to find the root for.
    /// @return The root of the set containing element x.
    auto find(const T &x) -> T;

    /// @brief Unites the sets that contain elements x and y.
    /// @param x First element
    /// @param y Second element
    /// @return True if the sets were successfully united, false if they were already in the same set.
    auto unionSets(const T &x, const T &y) -> bool;

    /// @brief Checks if elements x and y are in the same set.
    /// @param x First element
    /// @param y Second element
    /// @return True if x and y are connected (in the same set), false otherwise.
    auto connected(const T &x, const T &y) -> bool;

    std::unordered_map<T, T> parent;
    std::unordered_map<T, int32_t> rank;

  private:
    /// @brief Ensures that the element x is registered in the UnionSet.
    /// @param x The element to register.
    auto ensureRegistered(const T &x) -> void;
};

template <typename T> auto UnionSet<T>::find(const T &x) -> T
{
    ensureRegistered(x);
    if (parent[x] != x)
    {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

template <typename T> auto UnionSet<T>::unionSets(const T &x, const T &y) -> bool
{
    T rootX = find(x);
    T rootY = find(y);

    if (rootX == rootY)
        return false;

    if (rank[rootX] < rank[rootY])
    {
        parent[rootX] = rootY;
    }
    else if (rank[rootX] > rank[rootY])
    {
        parent[rootY] = rootX;
    }
    else
    {
        parent[rootY] = rootX;
        ++rank[rootX];
    }
    return true;
}

template <typename T> auto UnionSet<T>::connected(const T &x, const T &y) -> bool
{
    return find(x) == find(y);
}

template <typename T> auto UnionSet<T>::ensureRegistered(const T &x) -> void
{
    if (!parent.contains(x))
    {
        parent[x] = x;
        rank[x] = 1;
    }
}
} // namespace fox
