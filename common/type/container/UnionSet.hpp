#pragma once
#include <unordered_map>

namespace common {
template <typename T>
class UnionSet {
 public:
  auto find(const T& x) -> T;
  auto unionSets(const T& x, const T& y) -> bool;
  auto connected(const T& x, const T& y) -> bool;
  std::unordered_map<T, T> parent;
  std::unordered_map<T, int> rank;

 private:
  auto ensureRegistered(const T& x) -> void;
};

template <typename T>
auto UnionSet<T>::find(const T& x) -> T {
  ensureRegistered(x);
  if (parent[x] != x) {
    parent[x] = find(parent[x]);
  }
  return parent[x];
}

template <typename T>
auto UnionSet<T>::unionSets(const T& x, const T& y) -> bool {
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

template <typename T>
auto UnionSet<T>::connected(const T& x, const T& y) -> bool {
  return find(x) == find(y);
}

template <typename T>
auto UnionSet<T>::ensureRegistered(const T& x) -> void {
  if (!parent.contains(x)) {
    parent[x] = x;
    rank[x] = 1;
  }
}
}  // namespace common
