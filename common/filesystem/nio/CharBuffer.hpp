#pragma once
#include <string>

#include "interface/IBuffer.hpp"

namespace common
{
    class CharBuffer final : public IBuffer
    {
    public:
        explicit CharBuffer(size_t cap);
        auto compact() -> void;
        auto put(char c) -> void;
        auto put(const std::u16string& src) -> void;
        auto get() -> char16_t;
        [[nodiscard]] auto getRemaining() const -> std::string;

    private:
        std::string buffer_{};
    };
}
