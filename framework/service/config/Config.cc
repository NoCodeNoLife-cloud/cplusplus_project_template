#include "Config.hpp"

namespace framework::service::config {

auto Config::hasKey(const std::string& key) const -> bool { return params_.contains(key); }

auto Config::set(const std::string& key, const std::any& value) -> void { params_[key] = value; }

}  // namespace framework::service::config
