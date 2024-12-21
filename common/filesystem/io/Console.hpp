#pragma once
#include <format>
#include <iostream>
#include <string>

#include "interface/IFlushable.hpp"

namespace common
{
    class Console final : public IFlushable
    {
    public:
        template <typename... Args>
        auto format(const std::string& fmt, Args... args) -> void;
        template <typename... Args>
        auto printf(const std::string& fmt, Args... args) -> void;
        template <typename... Args>
        auto readLine(const std::string& fmt, Args... args) -> std::string;
        auto flush() -> void override;
        static auto readLine() -> std::string;
        static auto writer() -> std::ostream&;
        static auto reader() -> std::istream&;
    };

    template <typename... Args>
    auto Console::format(const std::string& fmt, Args... args) -> void
    {
        std::cout << std::vformat(fmt, std::make_format_args(args...));
    }

    template <typename... Args>
    auto Console::printf(const std::string& fmt, Args... args) -> void
    {
        format(fmt, args...);
    }

    template <typename... Args>
    auto Console::readLine(const std::string& fmt, Args... args) -> std::string
    {
        format(fmt, args...);
        return readLine();
    }
}
