#include "src/toolkit/StringToolkit.hpp"

#include <string>
#include <vector>

namespace common
{
    auto StringToolkit::split(const std::string& target,
                              const char split_char) noexcept
        -> std::vector<std::string>
    {
        std::vector<std::string> result;
        size_t start = 0;
        size_t pos = target.find(split_char);
        while (pos != std::string::npos)
        {
            result.push_back(target.substr(start, pos - start));
            start = pos + 1;
            pos = target.find(split_char, start);
        }
        result.push_back(target.substr(start));
        return result;
    }

    auto StringToolkit::concatenate(const std::vector<std::string>& source,
                                    const char split_char) noexcept
        -> std::string
    {
        if (source.empty())
            return "";
        std::string result = source[0];
        for (size_t i = 1; i < source.size(); ++i)
        {
            result += split_char;
            result += source[i];
        }
        return result;
    }
}
