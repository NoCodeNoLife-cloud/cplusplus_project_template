#pragma once
namespace common::iface
{
    template <typename T> class IComparable abstract
    {
    public:
        virtual ~IfaceComparable() = default;
        [[nodiscard]] virtual auto compareTo(const T& other) const -> int = 0;
        [[nodiscard]] virtual auto equals(const T& other) const -> bool = 0;
    };
}
