#include "src/filesystem/io/reader/Scanner.hpp"

#include <istream>
#include <stdexcept>

#include "src/task/ClientTask.hpp"

namespace common
{
    Scanner::Scanner(std::istream& input_stream) : input_(input_stream)
    {
    }

    auto Scanner::nextInt() const -> int32_t
    {
        if (std::string token; getNextToken(token))
        {
            try
            {
                return std::stoi(token);
            }
            catch (const std::exception&)
            {
                throw std::runtime_error("Failed to parse integer: " + token);
            }
        }
        throw std::runtime_error("No more integers available.");
    }

    auto Scanner::nextDouble() const -> double
    {
        if (std::string token; getNextToken(token))
        {
            try
            {
                return std::stod(token);
            }
            catch (const std::exception&)
            {
                throw std::runtime_error("Failed to parse double: " + token);
            }
        }
        throw std::runtime_error("No more doubles available.");
    }

    auto Scanner::nextLine() const -> std::string
    {
        std::string line;
        std::getline(input_, line);
        return line;
    }

    auto Scanner::getNextToken(std::string& token) const -> bool
    {
        // Skip leading whitespace
        while (input_.peek() != EOF && std::isspace(input_.peek()))
        {
            input_.get();
        }

        if (input_.peek() == EOF)
        {
            return false;
        }

        // Read until next whitespace
        token.clear();
        while (input_.peek() != EOF && !std::isspace(input_.peek()))
        {
            token += static_cast<char>(input_.get());
        }
        return true;
    }

    auto Scanner::nextTokens(const char delimiter) const -> std::vector<std::string>
    {
        std::string line;
        std::getline(input_, line);
        std::vector<std::string> tokens;
        boost::split(tokens, line, boost::is_any_of(std::string(1, delimiter)));

        // Remove empty tokens
        std::erase_if(tokens,
                      [](const std::string& s) { return s.empty(); });
        return tokens;
    }
}
