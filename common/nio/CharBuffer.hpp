#pragma once
#include <string>
#include <stdexcept>

#include "interface/IBuffer.hpp"

namespace common::nio
{
    class CharBuffer final : public interface::IBuffer
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
