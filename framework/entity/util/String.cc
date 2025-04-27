#include "String.hpp"

namespace framework::entity::util {
  auto String::split(const std::string& target, char splitChar) -> std::vector<std::string> {
    std::vector<std::string> result;
    size_t start = 0;
    size_t pos = target.find(splitChar);
    while (pos != std::string::npos) {
      result.push_back(target.substr(start, pos - start));
      start = pos + 1;
      pos = target.find(splitChar, start);
    }
    result.push_back(target.substr(start));
    return result;
  }
}
