#pragma once
#include <string>
#include <vector>

namespace framework::entity::util {
  class String {
  public:
    static auto split(const std::string& target, char splitChar) -> std::vector<std::string>;
  };
}
