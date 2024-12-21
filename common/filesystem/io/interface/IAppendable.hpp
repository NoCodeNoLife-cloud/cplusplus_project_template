#pragma once
#include <string>

namespace common
{
    template <typename T>
    class IAppendable abstract
    {
    public:
        virtual ~IAppendable() = default;
        virtual auto append(char c) -> T& = 0;
        virtual auto append(const std::string& str) -> T& = 0;
        virtual auto append(const std::string& str, size_t start, size_t end) -> T& = 0;
    };
}
