#pragma once
#include <unordered_map>

namespace framework::entity::data_structure {
  template <typename T>
  class UnionFind {
  public:
    T find(const T& x) {
      ensureRegistered(x);
      if (parent[x] != x) {
        parent[x] = find(parent[x]);
      }
      return parent[x];
    }

    bool unionSets(const T& x, const T& y) {
      T rootX = find(x);
      T rootY = find(y);

      if (rootX == rootY) return false;

      if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
      } else if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
      } else {
        parent[rootY] = rootX;
        ++rank[rootX];
      }
      return true;
    }

    bool connected(const T& x, const T& y) {
      return find(x) == find(y);
    }

  private:
    std::unordered_map<T, T> parent;
    std::unordered_map<T, int> rank;

    void ensureRegistered(const T& x) {
      if (!parent.contains(x)) {
        parent[x] = x;
        rank[x] = 1;
      }
    }
  };
} // namespace framework::entity::data_structure
