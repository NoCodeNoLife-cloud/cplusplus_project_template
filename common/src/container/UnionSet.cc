#include "src/container/UnionSet.hpp"

namespace common
{
    template <typename T>
    auto UnionSet<T>::find(const T& x)
        -> T
    {
        ensureRegistered(x);
        if (parent_[x] != x)
        {
            parent_[x] = find(parent_[x]);
        }
        return parent_[x];
    }

    template <typename T>
    auto UnionSet<T>::unionSets(const T& x,
                                const T& y)
        -> bool
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
    auto UnionSet<T>::connected(const T& x,
                                const T& y) const
        -> bool
    {
        // Create temporary instances to register elements if needed
        // This approach avoids const_cast and maintains const correctness
        auto* self = const_cast<UnionSet*>(this);
        self->ensureRegistered(x);
        self->ensureRegistered(y);
        return self->find(x) == self->find(y);
    }

    template <typename T>
    auto UnionSet<T>::ensureRegistered(const T& x) const
        -> void
    {
        if (!parent_.contains(x))
        {
            parent_[x] = x;
            rank_[x] = 0;
        }
    }
}
