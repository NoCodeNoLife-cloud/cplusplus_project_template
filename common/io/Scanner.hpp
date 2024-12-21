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
        explicit Scanner(std::istream& input_stream);
        [[nodiscard]] auto nextInt() const -> int;
        [[nodiscard]] auto nextDouble() const -> double;
        [[nodiscard]] auto nextLine() const -> std::string;
        auto getNextToken(std::string& token) const -> bool;
        [[nodiscard]] auto nextTokens(char delimiter = ' ') const -> std::vector<std::string>;
    private:
        std::istream& input_;
    };

    inline Scanner::Scanner(std::istream& input_stream): input_(input_stream) {}

    inline auto Scanner::nextInt() const -> int
    {
        if (std::string token; getNextToken(token))
        {
            return std::stoi(token);
        }
        throw std::runtime_error("No more integers available.");
    }

    inline auto Scanner::nextDouble() const -> double
    {
        if (std::string token; getNextToken(token))
        {
            return std::stod(token);
        }
        throw std::runtime_error("No more doubles available.");
    }

    inline auto Scanner::nextLine() const -> std::string
    {
        std::string line;
        std::getline(input_, line);
        return line;
    }

    inline auto Scanner::getNextToken(std::string& token) const -> bool
    {
        if (std::string line; std::getline(input_, line))
        {
            std::stringstream ss(line);
            ss >> token;
            return true;
        }
        return false;
    }

    inline auto Scanner::nextTokens(const char delimiter) const -> std::vector<std::string>
    {
        std::string line;
        std::getline(input_, line);
        std::vector<std::string> tokens;
        boost::split(tokens, line, boost::is_any_of(std::string(1, delimiter)));
        return tokens;
    }
}
