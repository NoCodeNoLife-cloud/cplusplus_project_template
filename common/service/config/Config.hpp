#pragma once
#include <any>
#include <string>
#include <unordered_map>

namespace common {
  class Config {
  public:
    template <typename T>
    auto get(const std::string& key) const -> T;
    [[nodiscard]] auto hasKey(const std::string& key) const -> bool;
    auto set(const std::string& key, const std::any& value) -> void;

  private:
    std::unordered_map<std::string, std::any> params_;
  };

  template <typename T>
  auto Config::get(const std::string& key) const -> T {
    return std::any_cast<T>(params_.at(key));
  }
}
