#pragma once
#include <string>

namespace common::iface
{
    template <typename T>
    class IfaceAppendable abstract
    {
    public:
        virtual ~IfaceAppendable() = default;
        virtual auto append(char c) -> T& = 0;
        virtual auto append(const std::string& str) -> T& = 0;
        virtual auto append(const std::string& str, size_t start, size_t end) -> T& = 0;
    };
}
