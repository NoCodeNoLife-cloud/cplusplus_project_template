#pragma once
#include <string>
#include <sstream>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>

namespace common::io
{
    class Scanner
    {
    public:
        explicit Scanner(std::istream& input_stream) : input_(input_stream)
        {
        }

        [[nodiscard]] auto nextInt() const -> int
        {
            if (std::string token; getNextToken(token))
            {
                return std::stoi(token);
            }
            throw std::runtime_error("No more integers available.");
        }

        [[nodiscard]] auto nextDouble() const -> double
        {
            if (std::string token; getNextToken(token))
            {
                return std::stod(token);
            }
            throw std::runtime_error("No more doubles available.");
        }

        [[nodiscard]] auto nextLine() const -> std::string
        {
            std::string line;
            std::getline(input_, line);
            return line;
        }

        auto getNextToken(std::string& token) const -> bool
        {
            if (std::string line; std::getline(input_, line))
            {
                std::stringstream ss(line);
                ss >> token;
                return true;
            }
            return false;
        }

        [[nodiscard]] auto nextTokens(const char delimiter = ' ') const -> std::vector<std::string>
        {
            std::string line;
            std::getline(input_, line);
            std::vector<std::string> tokens;
            boost::split(tokens, line, boost::is_any_of(std::string(1, delimiter)));
            return tokens;
        }

    private:
        std::istream& input_;
    };
}
