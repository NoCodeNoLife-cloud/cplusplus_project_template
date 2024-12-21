#pragma once
#include <format>
#include <iostream>
#include <string>
#include "interface/IfaceFlushable.hpp"

namespace common::io
{
    class Console final : public iface::IfaceFlushable
    {
    public:
        template <typename... Args>
        auto format(const std::string& fmt, Args... args) -> void
        {
            std::cout << std::vformat(fmt, std::make_format_args(args...));
        }

        template <typename... Args>
        auto printf(const std::string& fmt, Args... args) -> void
        {
            format(fmt, args...);
        }

        template <typename... Args>
        auto readLine(const std::string& fmt, Args... args) -> std::string
        {
            format(fmt, args...);
            return readLine();
        }

        auto flush() -> void override
        {
            std::cout.flush();
        }

        static auto readLine() -> std::string
        {
            std::string input;
            std::getline(std::cin, input);
            return input;
        }

        static auto writer() -> std::ostream&
        {
            return std::cout;
        }

        static auto reader() -> std::istream&
        {
            return std::cin;
        }
    };
}
